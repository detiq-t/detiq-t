#ifndef ALGORITHM_IDENTITY_H
#define ALGORITHM_IDENTITY_H

#include <algorithm>
#include <functional>

#include "../PixelAlgorithm.h"

namespace imagein {
    namespace algorithm {

    /*!
     * \brief Identity is an implementation of the identity using the PixelAlgorithm class.
     * This algorithm returns its unaltered parameter.
     * \tparam D A typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam I A templated class representing an Image type such as RgbImage_t. This classe will take the first template parameter D as its template parameter.
     */
      template <class I>
      class Identity : public PixelAlgorithm_t<I> {
         private:
              typedef typename I::depth_t D;
          
          protected:
              D pixelOp(D *pixel) const {
                  return *pixel;
              }
      };
}
}
#endif //!ALGORITHM_IDENTITY_H
