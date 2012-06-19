/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

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
