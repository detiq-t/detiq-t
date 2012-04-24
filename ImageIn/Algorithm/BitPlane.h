#ifndef ALGORITHM_BITPLANE_H
#define ALGORITHM_BITPLANE_H

#include "../Algorithm.h"
#include "../GrayscaleImage.h"
#include "../PixelAlgorithm.h"

namespace imagein {
	namespace algorithm {
	
    /*!
     * \brief BitPlane is a PixelAlgorithm which perform a bitwise and (~) with each pixel of an image and a given mask
     * \tparam D A typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam I A templated class representing an Image type such as RgbImage_t. This classe will take the first template parameter D as its template parameter.
     */
		template <class I>
		class BitPlane : public PixelAlgorithm_t<I> {
		  private:
        typedef typename I::depth_t D;

      public:
			
				BitPlane(D mask) : _mask(mask) {} 

			protected:
			
				D _mask;
				
				D pixelOp(D* pixel) const {
					return *pixel & _mask;
				}
		};
}
}
#endif //!ALGORITHM_BITPLANE_H
