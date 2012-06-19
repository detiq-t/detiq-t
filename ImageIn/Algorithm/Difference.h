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
