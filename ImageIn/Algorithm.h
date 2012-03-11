#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>

#include "Image.h"
#include "GenericAlgorithm.h"

namespace imagein
{
	template < typename Depth, template <typename Depth> class ImageType >
	class Algorithm_t : public GenericAlgorithm_t<Depth> {
		public:
			virtual ImageType<Depth>* operator() (const std::vector<const Image_t<Depth>*>&) const = 0;
			inline ImageType<Depth>* operator() (const Image_t<Depth>* img) { std::vector<const Image_t<Depth>*> imgs; imgs.push_back(img); (*this)(imgs); }
	};

	template <template <typename Depth> class ImageType >
	class Algorithm_8 : public Algorithm_t<uint8_t, ImageType> {
			virtual ImageType<uint8_t>*
			operator() (const std::vector<const Image_8*>&) const = 0;
			inline ImageType<uint8_t>* operator() (const Image_8* img) { std::vector<const Image_8*> imgs; imgs.push_back(img); (*this)(imgs); }
	};

	template <template <typename Depth> class ImageType >
	class Algorithm_16 : public Algorithm_t<uint16_t, ImageType> {
			virtual ImageType<uint16_t>* operator() (const std::vector<const Image_16*>&) const = 0;
			inline ImageType<uint16_t>* operator() (const Image_16* img) { std::vector<const Image_16*> imgs; imgs.push_back(img); (*this)(imgs); }
	};

	template <template <typename Depth> class ImageType >
	class Algorithm_32 : public Algorithm_t<uint32_t, ImageType> {
			virtual ImageType<uint32_t>* operator() (const std::vector<const Image_32*>&) const = 0;
			inline ImageType<uint32_t>* operator() (const Image_32* img) { std::vector<const Image_32*> imgs; imgs.push_back(img); (*this)(imgs); }
	};
}

#endif //!ALGORITHM_H