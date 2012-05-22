#ifndef ALGORITHM_DIFFERENCE_H
#define ALGORITHM_DIFFERENCE_H

#include <algorithm>
#include <functional>

#include "../PixelAlgorithm.h"

namespace imagein {
    namespace algorithm {

    /*!
     * \brief Difference<I, A> is a PixelAlgorithm which perform the difference of 2 images
     * \tparam I A templated class representing an Image type such as RgbImage_t. This classe will take the first template parameter D as its template parameter.
     */
    template <class I>
    class Difference : public PixelAlgorithm_t<I, 2> {
        private:
            typedef typename I::depth_t D;
        
        protected:

            /*!
             * \brief When a PixelAlgorithm is applied, the pixelOp method is called to determine the value of each pixel of the resulting image
             */
            D pixelOp(D pixel[2]) const {
                return pixel[0] - pixel[1];
            }
    };
}
}
#endif //!ALGORITHM_AVERAGE_H
