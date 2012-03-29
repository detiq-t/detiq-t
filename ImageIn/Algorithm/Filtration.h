#ifndef FILTRAGE_H
#define FILTRAGE_H

#include "../Image.h"
#include "../Algorithm.h"
#include "Matrix.h"

namespace imagein
{
	namespace algorithm
	{
		template <typename D>
		class Filtration_t : public Algorithm_t<Image_t<D>, 1>
		{
		public:
			Filtration_t(const Filter& filter): _filter(filter) {}
			
			static Filtration uniformBlur(int coef, int nbPixels);
			static Filtration prewitt(bool vertical, int nbPixels);
			
		protected:
			Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
		
		private:
			const Filter& _filter;
		};
		
		typedef Filtration_t<depth_default_t> Filtration; //!< Standard Algorithm with default depth. See Image_t::depth_default_t
	}
}

#include "Filtration.tpp"

#endif //FILTRAGE_H