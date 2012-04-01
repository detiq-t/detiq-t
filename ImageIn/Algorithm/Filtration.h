#ifndef FILTRAGE_H
#define FILTRAGE_H

#include <cmath>
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
		public:
			Filtration_t(Filter& filter) : _filter(filter) {}
			Filtration_t(const Filtration_t & f) : _filter(f._filter) {}

      //#ifdef __linux_
      //static parallelAlgorithm(Filtration* this, Image_t<D*> img, int infx, supx);
      //#endif
			
			static Filtration_t<D> uniformBlur(int coef, int nbPixels);
			static Filtration_t<D> prewitt(bool vertical, int nbPixels);
			static Filtration_t<D> gaussianBlur(double alpha);

			
			Filter _filter;
			
		//protected:
			Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
		
		private:
		};
		
		typedef Filtration_t<depth_default_t> Filtration; //!< Standard Algorithm Filtration with default depth.
	}
}

#include "Filtration.tpp"

#endif //FILTRAGE_H
