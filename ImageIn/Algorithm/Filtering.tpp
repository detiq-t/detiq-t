//#include "Filtering.h"

#include <algorithm>
#include <pthread.h>
#include "Average.h"

namespace imagein
{
	namespace algorithm
	{
		template <typename D>
		Filtering_t<D>::Filtering_t(Filter* filter)
		{
			_filters.push_back(filter);
			_policy = blackPolicy;
			_normalization = zeroNormalization;
		}
		
		template <typename D>
		Filtering_t<D>::Filtering_t(std::vector<Filter*> filters) : _filters(filters)
		{
			_policy = blackPolicy;
			_normalization = zeroNormalization;
		}
		
		template <typename D>
		Image_t<D>* Filtering_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
		{
		  const Image_t<D>* img = dynamic_cast<const Image_t<D>*>(imgs.at(0));
		  
		  if(img == NULL) {
			throw ImageTypeException(__LINE__, __FILE__);
		  }
		  
		  int posFactor = 0;
		  int negFactor = 0;
	  
		  int width = img->getWidth();
		  int height = img->getHeight();
		  int nChannels = img->getNbChannels();
		  
		  std::vector<Filter*>::iterator filter;
		  std::vector<Image_t<D>*> images;
		  
		  for(filter = _filters.begin(); filter != _filters.end(); ++filter)
		  {
			  Filter::iterator iter = (*filter)->begin();
			  for(iter; iter != (*filter)->end(); ++iter)
			  {
				if((*iter) < 0)
				  negFactor += (*iter);
				else
				  posFactor += (*iter);
			  }
			  
			  int factor;
			  if(posFactor >= -negFactor)
				factor = posFactor;
			  else
				factor = -negFactor;
			  
			  int halfHeightFilter = (*filter)->height() / 2;
			  int halfWidthFilter = (*filter)->width() / 2;
			  
			  Image_t<D>* result = new Image_t<D>(width, height, nChannels);
			  
			  #ifdef __linux__
				  int numCPU = sysconf( _SC_NPROCESSORS_ONLN );
			  
				  pthread_t threads[numCPU];
				  
				  int inf = 0;
				  for(int i = 0; i < numCPU; i++)
				  {
					  pthread_t thread;
					  pthread_attr_t attr;
					  pthread_attr_init(&attr);
					  
					  struct ParallelArgs* args = new struct ParallelArgs;
					  args->img = img;
					  args->result = result;
					  args->filter = *filter;
					  args->policy = _policy;
					  args->normalization = _normalization;
					  args->infx = inf;
					  args->supx = width / (numCPU - i);
					  args->factor = factor;			  
					  pthread_create(&thread, &attr, parallelAlgorithm, (void*)args);
					  
					  inf = inf + (width / numCPU);
					  threads[i] = thread;
				  }
				  
				  for(int i = 0; i < numCPU; i++)
					pthread_join(threads[i], NULL);	  
				  
			  #endif
		      
			  #ifndef __linux__
				  for(int x = 0; x < width; x++)
				  {
					for(int y = 0; y < height; y++)
					{
					  for(int channel = 0; channel < nChannels; channel++)
					  {
						int newPixel = 0;

						for(int i = 0; i < (*filter)->width(); i++)
						{
						  for(int j = 0; j < (*filter)->height(); j++)
						  {
							newPixel += (**filter)[i][j] * ((*_policy)(img, x + i - halfWidthFilter, y + j - halfHeightFilter, channel));
						  }
						}

						if(factor != 0)
						{
						  newPixel /= factor;

						  if(newPixel < 0)
							newPixel = ((*_normalization)(newPixel));
						}
						result->setPixel(x, y, channel, newPixel);
					  }
					}
				  }
			  #endif
			  images.push_back(result);
		  }
		  Image_t<D>* result = NULL;
		  
		  if(images.size() == 1)
			result = images[0];
		  else
		  {
			  unsigned int size = images.size();
			  Average<Image_t<D>, 2> av;
			  
			  for(int i = 0; i < size; ++i)
			  {
				  if(result == NULL)
				  {
					result = av(images[0], images[1]);
				  }
				  else
				  {
					result = av(result, images[i]);
				  }
			  }
		  }
		  return result;
		}
		
		template <typename D>
		void* Filtering_t<D>::parallelAlgorithm(void* data)
		{
			struct ParallelArgs args = *((ParallelArgs*) data);
			
			const Image_t<D>* img = args.img;
			Image_t<D>* result = args.result;
			Filter* filter = args.filter;
			Policy policy = args.policy;
			Normalization normalization = args.normalization;
			int infx = args.infx;
			int supx = args.supx;
			int factor = args.factor;
			
			int halfHeightFilter = filter->height() / 2;
			int halfWidthFilter = filter->width() / 2;
			for(int x = infx; x < supx; x++)
			{
				for(int y = 0; y < img->getHeight(); y++)
				{
				  for(int channel = 0; channel < img->getNbChannels(); channel++)
				  {
					int newPixel = 0;

					for(int i = 0; i < filter->width(); i++)
					{
					  for(int j = 0; j < filter->height(); j++)
					  {
						newPixel += (*filter)[i][j] * ((*policy)(img, x + i - halfWidthFilter, y + j - halfHeightFilter, channel));
					  }
					}

					if(factor != 0)
					{
					  newPixel /= factor;

					  if(newPixel < 0)
						newPixel = ((*normalization)(newPixel));
					}
					result->setPixel(x, y, channel, newPixel);
				  }
				}
			}
			delete (ParallelArgs*) data;
			if(supx != img->getWidth())
				pthread_exit(NULL);
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::uniformBlur(int coef = 1, int numPixels = 3)
		{
			Filter* filter = new Filter(numPixels, numPixels);
			for(int i = 0; i < numPixels; i++)
			{
				for(int j = 0; j < numPixels; j++)
				{
					(*filter)[i][j] = coef;
				}
			}
			return Filtering_t<D>(filter);
		}

		template <typename D>
		Filtering_t<D> Filtering_t<D>::gaussianBlur(double alpha)
		{
		  std::vector<double> gaussCoef;
		  double min(0);

		  for (int i = 0; ; i++)
		  {
			double coef = 10000.0 * std::exp(-(std::pow(i, 2.0)) / (2.0 * std::pow(alpha, 2))) / (2 * M_PI * std::pow(alpha, 2));
			if (i == 0) min = coef / 10 + 1;
			if (coef < min)
			  break;
			else
			  gaussCoef.push_back(coef);
		  }

		  std::cout << gaussCoef.size() * 2 - 1 << std::endl;

		  Filter f(gaussCoef.size() * 2 - 1, gaussCoef.size() * 2 - 1);
		  int center = gaussCoef.size() - 1;

		  for(int i = 0; i < gaussCoef.size(); i++)
		  {
			for(int j = i; j < gaussCoef.size(); j++)
			{
			  if(i == 0) /* values are already in gaussCoef, so no compute needed */
			  {
				f[center][center + j] = gaussCoef[j];

				if(j != 0)
				{
				  f[center][center - j] = gaussCoef[j];
				  f[center - j][center] = gaussCoef[j];
				  f[center + j][center] = gaussCoef[j];
				}
			  }
			  else
			  {
				double coef = 10000.0 * std::exp(-(std::pow(i, 2) + std::pow(j, 2)) / (2 * std::pow(alpha, 2))) / (2 * M_PI * std::pow(alpha, 2));

				f[center + i][center + j] = coef;
				f[center + i][center - j] = coef;
				f[center - i][center + j] = coef;
				f[center - i][center - j] = coef;
				f[center + j][center + i] = coef;
				f[center + j][center - i] = coef;
				f[center - j][center + i] = coef;
				f[center - j][center - i] = coef;
			  } 
			}
		  }
		  return Filtering_t<D>(f);
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::prewitt(int coef = 1, int numPixels = 3)
		{
			std::vector<Filter*> filters;
			
			for(int vertical = 1 ; vertical >= 0 ; --vertical)
			{
				int width = 3, height = 3;
				
				if(vertical == 1) height = numPixels;
				else width = numPixels;
				
				Filter* filter = new Filter(width, height);
				for(int i = 0; i < width; i++)
				{
					for(int j = 0; j < height; j++)
					{
						if(vertical == 1 && i == 0 || vertical == 0 && j == 0)
							(*filter)[i][j] = -coef;
						else if(vertical == 1 && i == width - 1 || vertical == 0 && j == height - 1)
							(*filter)[i][j] = coef;
						else
							(*filter)[i][j] = 0;
					}
				}
				filters.push_back(filter);
			}
			return Filtering_t<D>(filters);
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::roberts(int coef = 1)
		{
			std::vector<Filter*> filters;
			
			for(int h = 1 ; h >= 0 ; --h)
			{				
				Filter* filter = new Filter(3, 3);
				for(int i = 0; i < 3; ++i)
				{
					for(int j = 0; j < 3; ++j)
					{
						if(h == 1 && i == 1 && j == 2 || h == 0 && i == 1 && j == 1)
							(*filter)[i][j] = -coef;
						else if(h == 1 && i == 2 && j == 1 || h == 0 && i == 2 && j == 2)
							(*filter)[i][j] = coef;
						else
							(*filter)[i][j] = 0;
					}
				}
				filters.push_back(filter);
			}
			
			return Filtering_t<D>(filters);
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::sobel(int coef = 1)
		{
			std::vector<Filter*> filters;
			
			for(int vertical = 1 ; vertical >= 0 ; --vertical)
			{
				int width = 3, height = 3;
				
				Filter* filter = new Filter(width, height);
				for(int i = 0; i < width; i++)
				{
					for(int j = 0; j < height; j++)
					{
						if(vertical == 1)
						{
							if(i == 0)
								if(j == 1) (*filter)[i][j] = -(2 * coef);
								else (*filter)[i][j] = -coef;
							else if(i == 2)
								if(j == 1) (*filter)[i][j] = 2 * coef;
								else (*filter)[i][j] = coef;
							else (*filter)[i][j] = 0; 
						}
						else
						{
							if(j == 0)
								if(i == 1) (*filter)[i][j] = -(2 * coef);
								else (*filter)[i][j] = -coef;
							else if(j == 2)
								if(i == 1) (*filter)[i][j] = 2 * coef;
								else (*filter)[i][j] = coef;
							else (*filter)[i][j] = 0;
						}
					}
				}
				filters.push_back(filter);
			}
			return Filtering_t<D>(filters);
		}
	}
}
