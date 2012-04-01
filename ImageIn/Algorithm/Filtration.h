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
		class Filtration_t : public Algorithm_t<Image_t<D>, 1>
		{
			typedef D (*Politic)(const Image_t<D>*, const int&, const int&, const int&);
		public:
			Filtration_t(Filter& filter);
			Filtration_t(const Filtration_t& f) : _filter(f._filter), _politic(f._politic) {}

			inline void setPolitic(Politic politic) { _politic = politic; }
			
			static Filtration_t<D> uniformBlur(int coef, int nbPixels);
			static Filtration_t<D> prewitt(bool vertical, int nbPixels);
			static Filtration_t<D> gaussianBlur(double alpha);

			static D blackPolitic(const Image_t<D>* img, const int& x, const int& y, const int& channel)
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
			
			static D mirrorPolitic(const Image_t<D>* img, const int& x, const int& y, const int& channel)
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
			
			static D nearestPolitic(const Image_t<D>* img, const int& x, const int& y, const int& channel)
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
			
			static D sphericalPolitic(const Image_t<D>* img, const int& x, const int& y, const int& channel)
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
			
		protected:
			#ifdef __linux__
			static void* parallelAlgorithm(void* data);
			#endif
			
			Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
		
		private:
			Filter _filter;
			Politic _politic;
			
			struct ParallelArgs
			{
				const Image_t<D>* img;
				Image_t<D>* result;
				Filter* filter;
				Politic politic;
				int infx;
				int supx;
				int factor;
			};
		};
		typedef Filtration_t<depth_default_t> Filtration; //!< Standard Algorithm Filtration with default depth.
	}
}

#include "Filtration.tpp"

#endif //FILTRAGE_H
