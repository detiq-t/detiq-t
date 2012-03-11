#ifndef GENERICALGORITHM_H
#define GENERICALGORITHM_H

#include "Image.h"

namespace imagein
{
	template <typename D>
	class GenericAlgorithm_t {
		public:
			virtual Image_t<D>* operator() (const std::vector<const Image_t<D>*>&) const = 0;
			inline Image_t<D>* operator() (const Image_t<D>* img) { std::vector<const Image_t<D>*> imgs; imgs.push_back(img); (*this)(imgs); }
		private:
	};
}

#endif //!GENERICALGORITHM_H