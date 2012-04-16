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
			  for(; iter != (*filter)->end(); ++iter)
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
			  
			  for(unsigned int i = 0; i < size; ++i)
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
			unsigned int infx = args.infx;
			unsigned int supx = args.supx;
			int factor = args.factor;
			
			int halfHeightFilter = filter->height() / 2;
			int halfWidthFilter = filter->width() / 2;
			for(unsigned int x = infx; x < supx; x++)
			{
				for(unsigned int y = 0; y < img->getHeight(); y++)
				{
				  for(unsigned int channel = 0; channel < img->getNbChannels(); channel++)
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
			return Filtering_t<D>(Filter::uniform(coef, numPixels));
		}

		template <typename D>
		Filtering_t<D> Filtering_t<D>::gaussianBlur(double alpha)
		{
			return Filtering_t<D>(Filter::gaussian(alpha));
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::prewitt(int coef = 1, int numPixels = 3)
		{
			return Filtering_t<D>(Filter::prewitt(coef, numPixels));
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::roberts(int coef = 1)
		{
			return Filtering_t<D>(Filter::roberts(coef));
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::sobel(int coef = 1)
		{
			return Filtering_t<D>(Filter::sobel(coef));
    }
	}
}
