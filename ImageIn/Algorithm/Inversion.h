#ifndef ALGORITHM_INVERSION_H
#define ALGORITHM_INVERSION_H

#include "../Algorithm.h"

namespace imagein {
	namespace algorithm {
	
    /*!
     * \brief Average is a PixelAlgorithm which perform the inversion of an image
     * \tparam D A typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam I A templated class representing an Image type such as RgbImage_t. This classe will take the first template parameter D as its template parameter.
     */
		template < typename D, template <typename D> class I>
		class Inversion : public PixelAlgorithm_t<D, I, 1> {

			protected:
				
				D pixelOp(D *pixel) const {
					return ~*pixel;
				}
		};
}
}
#endif //!ALGORITHM_INVERSION_H
