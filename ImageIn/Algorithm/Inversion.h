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
		template <class I>
		class Inversion : public PixelAlgorithm_t<I, 1> {
      private:
          typedef typename I::depth_t D;

			protected:
				
				D pixelOp(D *pixel) const {
					return ~*pixel;
				}
		};
}
}
#endif //!ALGORITHM_INVERSION_H
