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
		template <typename D>
		class Filtering_t : public Algorithm_t<Image_t<D>, 1>
		{
			typedef D (*Policy)(const Image_t<D>*, const int&, const int&, const int&);
			typedef D (*Normalization)(int);
		public:
			Filtering_t(Filter* filter);
			Filtering_t(std::vector<Filter*> filters);
			Filtering_t(const Filtering_t& f) : _filters(f._filters), _policy(f._policy), _normalization(f._normalization) {}

			inline void setPolitic(Policy policy) { _policy = policy; }
			inline void setNormalization(Normalization normalization) { _normalization = normalization; }
			
			static Filtering_t<D> uniformBlur(int coef, int numPixels);
			static Filtering_t<D> gaussianBlur(double alpha);
			static Filtering_t<D> prewitt(int coef, int numPixels);
			static Filtering_t<D> roberts(int coef);
			static Filtering_t<D> sobel(int coef);

			static D blackPolicy(const Image_t<D>* img, const int& x, const int& y, const int& channel)
			{
				D newPixel;
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
			
			static D mirrorPolicy(const Image_t<D>* img, const int& x, const int& y, const int& channel)
			{
				D newPixel;
				try
				{
					newPixel = img->getPixel(x, y, channel);
				}
				catch(std::out_of_range)
				{
					int nx = x, ny = y;
					if(x < 0)
						nx = -x;
					else if(x >= img->getWidth())
						nx = img->getWidth() - (x - img->getWidth());
					if(y < 0)
						ny = -y;
					else if(y >= img->getHeight())
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
			
			static D nearestPolicy(const Image_t<D>* img, const int& x, const int& y, const int& channel)
			{
				D newPixel;
				try
				{
					newPixel = img->getPixel(x, y, channel);
				}
				catch(std::out_of_range)
				{
					int nx = x, ny = y;
					if(x < 0)
						nx = 0;
					else if(x >= img->getWidth())
						nx = img->getWidth() - 1;
					if(y < 0)
						ny = 0;
					else if(y >= img->getHeight())
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
			
			static D sphericalPolicy(const Image_t<D>* img, const int& x, const int& y, const int& channel)
			{
				D newPixel;
				try
				{
					newPixel = img->getPixel(x, y, channel);
				}
				catch(std::out_of_range)
				{
					int nx = x, ny = y;
					if(x < 0)
						nx = img->getWidth() - x;
					else if(x >= img->getWidth())
						nx = x - img->getWidth();
					if(y < 0)
						ny = img->getHeight() - y;
					else if(y >= img->getHeight())
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
			
			static D zeroNormalization(int){ return 0; }
			
			static D absoluteNormalization(int i){ return i < 0 ? -i : i; }
			
			static D scaleNormalization(int i){ return 255 / 2 + i / 2; }
			
		protected:
			#ifdef __linux__
			static void* parallelAlgorithm(void* data);
			#endif
			
			Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
		
		private:
			std::vector<Filter*> _filters;
			Policy _policy;
			Normalization _normalization;
			
			struct ParallelArgs
			{
				const Image_t<D>* img;
				Image_t<D>* result;
				Filter* filter;
				Policy policy;
				Normalization normalization;
				int infx;
				int supx;
				int factor;
			};
		};
		typedef Filtering_t<depth_default_t> Filtering; //!< Standard Algorithm Filtering with default depth.
	}
}

#include "Filtering.tpp"

#endif //FILTRAGE_H
