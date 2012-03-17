#ifndef ALGORITHM_IDENTITY_H
#define ALGORITHM_IDENTITY_H

#include <algorithm>
#include <functional>

#include "../PixelAlgorithm.h"

namespace imagein {
    namespace algorithm {

        template <typename D, template <typename D> class I>
        class Identity : public PixelAlgorithm_t<D, I> {

            protected:

                D pixelOp(D *pixel) const {
                    return *pixel;
                }
        };
}
}
#endif //!ALGORITHM_IDENTITY_H
