#ifndef ALGORITHM_BITPLANE_H
#define ALGORITHM_BITPLANE_H

#include "../Algorithm.h"
#include "../GrayscaleImage.h"

namespace imagein {
	namespace algorithm {
	
		template <typename D, template <typename D> class I>
		class BitPlane : public PixelAlgorithm_t<D, I > {
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
