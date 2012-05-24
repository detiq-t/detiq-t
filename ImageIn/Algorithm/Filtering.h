#ifndef FILTRAGE_H
#define FILTRAGE_H

#include <vector>
#include <pthread.h>

#include "../Image.h"
#include "../Algorithm.h"
#include "Filter.h"

namespace imagein
{
	namespace algorithm
	{		
		class Filtering : public Algorithm_t<Image_t<int>, 1>
		{
			typedef int (*Policy)(const Image_t<int>*, const int&, const int&, const int&);
			
		public:
			Filtering(Filter* filter);
			Filtering(std::vector<Filter*> filters);
			Filtering(const Filtering& f) : _filters(f._filters), _policy(f._policy) {}
  
			inline void setPolicy(Policy policy) { _policy = policy; }
			
			static Filtering uniformBlur(int numPixels);
			static Filtering gaussianBlur(double alpha);
			static Filtering prewitt(int numPixels);
			static Filtering roberts();
			static Filtering sobel();
			static Filtering squareLaplacien();

			static int blackPolicy(const Image_t<int>* img, const int& x, const int& y, const int& channel)
			{
				int newPixel;
				try
				{
					newPixel = img->getPixel(x, y, channel);
				}
				catch(std::out_of_range)
				{
					newPixel = 0;
				}
				return newPixel;
			}
			
			static int mirrorPolicy(const Image_t<int>* img, const int& x, const int& y, const int& channel)
			{
				int newPixel;
				try
				{
					newPixel = img->getPixel(x, y, channel);
				}
				catch(std::out_of_range)
				{
					int nx = x, ny = y;
					if(x < 0)
						nx = -x;
					else if(x >= (int)img->getWidth())
						nx = img->getWidth() - (x - img->getWidth());
					if(y < 0)
						ny = -y;
					else if(y >= (int)img->getHeight())
						ny = img->getHeight() - (y - img->getHeight());
					
					try
					{
						newPixel = img->getPixel(nx, ny, channel);
					}
					catch(std::out_of_range)
					{
						newPixel = 0;
					}
				}
				return newPixel;
			}
			
			static int nearestPolicy(const Image_t<int>* img, const int& x, const int& y, const int& channel)
			{
				int newPixel;
				try
				{
					newPixel = img->getPixel(x, y, channel);
				}
				catch(std::out_of_range)
				{
					int nx = x, ny = y;
					if(x < 0)
						nx = 0;
					else if(x >= (int)img->getWidth())
						nx = img->getWidth() - 1;
					if(y < 0)
						ny = 0;
					else if(y >= (int)img->getHeight())
						ny = img->getHeight() - 1;
					
					try
					{
						newPixel = img->getPixel(nx, ny, channel);
					}
					catch(std::out_of_range)
					{
						newPixel = 0;
					}
				}
				return newPixel;
			}
			
			static int sphericalPolicy(const Image_t<int>* img, const int& x, const int& y, const int& channel)
			{
				int newPixel;
				try
				{
					newPixel = img->getPixel(x, y, channel);
				}
				catch(std::out_of_range)
				{
					int nx = x, ny = y;
					if(x < 0)
						nx = img->getWidth() - x;
					else if(x >= (int)img->getWidth())
						nx = x - img->getWidth();
					if(y < 0)
						ny = img->getHeight() - y;
					else if(y >= (int)img->getHeight())
						ny = y - img->getHeight();
					
					try
					{
						newPixel = img->getPixel(nx, ny, channel);
					}
					catch(std::out_of_range)
					{
						newPixel = 0;
					}
				}
				return newPixel;
			}
			
		protected:
			#ifdef __linux__
			static void* parallelAlgorithm(void* data);
			#endif
			
			Image_t<int>* algorithm(const std::vector<const Image_t<int>*>& imgs);
		
		private:
			std::vector<Filter*> _filters;
			Policy _policy;
			
			#ifdef __linux__
			struct ParallelArgs
			{
				const Image_t<int>* img;
				Image_t<int>* result;
				Filter* filter;
				Policy policy;
				int infx;
				int supx;
				int factor;
        bool odd;
			};
			#endif
		};
	}
}

#endif //FILTRAGE_H

