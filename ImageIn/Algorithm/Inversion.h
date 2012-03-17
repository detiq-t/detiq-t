#ifndef ALGORITHM_INVERSION_H
#define ALGORITHM_INVERSION_H

#include "../Algorithm.h"

namespace imagein {
	namespace algorithm {
	
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
