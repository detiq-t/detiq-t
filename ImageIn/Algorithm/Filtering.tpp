//#include "Filtering.h"

#include <algorithm>
#include <pthread.h>
#include <sys/sysinfo.h>
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
			/*
       * _normalization = zeroNormalization;
       */
		}
		
		template <typename D>
		Filtering_t<D>::Filtering_t(std::vector<Filter*> filters) : _filters(filters)
		{
			_policy = blackPolicy;
			/*
       * _normalization = zeroNormalization;
       */
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
      bool neg = false;
	  
		  int width = img->getWidth();
		  int height = img->getHeight();
		  int nChannels = img->getNbChannels();
      bool odd = width % 2 != 1 || height % 2 != 1;
		  
		  std::vector<Filter*>::iterator filter;
		  std::vector<Image_t<D>*> images;
		  
		  for(filter = _filters.begin(); filter != _filters.end(); ++filter)
		  {
			  Filter::iterator iter = (*filter)->begin();
			  for(; iter != (*filter)->end(); ++iter)
			  {
          if((*iter) < 0)
          {
            negFactor += (*iter);
            neg = true;
          }
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
          int numCPU;
          #ifdef _SC_NPROCESSORS_ONLN
            numCPU = sysconf( _SC_NPROCESSORS_ONLN );
          #else
            numCPU = get_nprocs_conf ();
          #endif
			  
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
					  /*
             * args->normalization = _normalization;
             */
					  args->infx = inf;
					  args->supx = width / (numCPU - i);
					  args->factor = factor;
            args->neg = neg;
            args->odd = odd;
            
					  pthread_create(&thread, &attr, parallelAlgorithm, (void*)args);
					  
					  inf = inf + (width / numCPU);
					  threads[i] = thread;
				  }
				  
				  for(int i = 0; i < numCPU; i++)
					pthread_join(threads[i], NULL);	  
				  
			  #else
        
          int halfHeightFilter = (*filter)->height() / 2;
          int halfWidthFilter = (*filter)->width() / 2;
          
				  for(int x = 0; x < width; x++)
				  {
            for(int y = 0; y < height; y++)
            {
              for(int channel = 0; channel < nChannels; channel++)
              {
                double newPixel = 0;

                for(int i = 0; i < (*filter)->width(); i++)
                {
                  for(int j = 0; j < (*filter)->height(); j++)
                  {
                    if(odd)
                    {
                      newPixel += (**filter)[i][j] * ((*_policy)(img, x + i - halfWidthFilter, y + j - halfHeightFilter, channel));
                    }
                    else
                    {
                      newPixel += (**filter)[i][j] * ((*_policy)(img, x + i - halfWidthFilter - 1, y + j - halfHeightFilter - 1, channel));
                    }
                  }
                }
                
                if(factor != 0)
                {
                  newPixel /= factor;
                  
                  if(neg)
                  {
                    newPixel += 127;
                    if(newPixel > 255) newPixel = 255;
                    else if(newPixel < 0) newPixel = 0;
                  }
                  
                  /*
                   * if(newPixel < 0)
                   * newPixel = ((*_normalization)(newPixel));
                   */
                }
                result->setPixel(x, y, channel, (int)newPixel);
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
			/*
       * Normalization normalization = args.normalization;
       */
			unsigned int infx = args.infx;
			unsigned int supx = args.supx;
			int factor = args.factor;
      bool neg = args.neg;
      bool odd = args.odd;
			
			int halfHeightFilter = filter->height() / 2;
			int halfWidthFilter = filter->width() / 2;
			for(int x = infx; x < supx; x++)
			{
				for(int y = 0; y < img->getHeight(); y++)
				{
				  for(unsigned int channel = 0; channel < img->getNbChannels(); channel++)
				  {
            double newPixel = 0;

            for(int i = 0; i < filter->width(); i++)
            {
              for(int j = 0; j < filter->height(); j++)
              {
                 int p;
                 if(odd)
                 {
                   p = (*filter)[i][j] * ((*policy)(img, x + i - halfWidthFilter, y + j - halfHeightFilter, channel));
                 }
                 else
                 {
                   p = (*filter)[i][j] * ((*policy)(img, x + i - halfWidthFilter - 1, y + j - halfHeightFilter - 1, channel));
                 }
                 newPixel += p;
              }
            }

            if(factor != 0)
            {
              newPixel /= factor;
              
              if(neg)
              {
                newPixel += 127;
                if(newPixel > 255) newPixel = 255;
                else if(newPixel < 0) newPixel = 0;
              }

              /*
               * if(newPixel < 0)
               * newPixel = ((*normalization)(newPixel));
               */
            }
            result->setPixel(x, y, channel, (int)newPixel);
				  }
				}
			}
			delete (ParallelArgs*) data;
			if(supx != img->getWidth())
				pthread_exit(NULL);
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::uniformBlur(int numPixels = 3)
		{
			return Filtering_t<D>(Filter::uniform(numPixels));
		}

		template <typename D>
		Filtering_t<D> Filtering_t<D>::gaussianBlur(double alpha)
		{
			return Filtering_t<D>(Filter::gaussian(alpha));
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::prewitt(int numPixels = 3)
		{
			return Filtering_t<D>(Filter::prewitt(numPixels));
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::roberts()
		{
			return Filtering_t<D>(Filter::roberts());
		}
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::sobel()
		{
			return Filtering_t<D>(Filter::sobel());
    }
		
		template <typename D>
		Filtering_t<D> Filtering_t<D>::squareLaplacien()
		{
			return Filtering_t<D>(Filter::squareLaplacien());
    }
	}
}
