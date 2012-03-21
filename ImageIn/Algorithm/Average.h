#ifndef ALGORITHM_AVERAGE_H
#define ALGORITHM_AVERAGE_H

#include <algorithm>
#include <functional>

#include "../PixelAlgorithm.h"

namespace imagein {
    namespace algorithm {

    /*!
     * \brief Average<D, I, A> is a PixelAlgorithm which perform the mean average of A images
     * \tparam D A typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam I A templated class representing an Image type such as RgbImage_t. This classe will take the first template parameter D as its template parameter.
     * \tparam A An unsigned integer corresponding to the Arity of the algorithm, i.e. the number of images the algorithm takes as parameters
     */
    template <class I, unsigned int A>
    class Average : public PixelAlgorithm_t<I, A> {
        private:
            typedef typename I::depth_t D;
        
        protected:

            /*!
             * \brief When a PixelAlgorithm is applied, the pixelOp method is called to determine the value of each pixel of the resulting image
             */
            D pixelOp(D pixel[A]) const {
                D result = 0;
                for(unsigned int i=0; i<A; ++i) {
                    result += pixel[i];
                }
                return result/A;
            }
    };
}
}
#endif //!ALGORITHM_AVERAGE_H
