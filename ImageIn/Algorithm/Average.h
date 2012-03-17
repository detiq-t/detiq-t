#ifndef ALGORITHM_AVERAGE_H
#define ALGORITHM_AVERAGE_H

#include <algorithm>
#include <functional>

#include "../PixelAlgorithm.h"

namespace imagein {
    namespace algorithm {

        template <typename D, template <typename D> class I, unsigned int A>
        class Average : public PixelAlgorithm_t<D, I, A> {

            protected:

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
