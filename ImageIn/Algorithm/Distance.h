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

#ifndef ALGORITHM_DISTANCE_H
#define ALGORITHM_DISTANCE_H

#include <algorithm>
#include <functional>
#include <cmath>

#include "../PixelAlgorithm.h"

namespace imagein
{
  namespace algorithm
  {

    template <class I, unsigned int A>
    class EuclideanDistance : public PixelAlgorithm_t<I, A>
    {
    private:
      typedef typename I::depth_t D;
          
    protected:
      D pixelOp(D pixel[A]) const
      {
        D result = 0;
        for(unsigned int i=0; i < A; i++)
        {
          result += pixel[i] * pixel[i];
        }

        return std::sqrt(result);
      }
    };

    template <class I, unsigned int A>
    class MaxDistance : public PixelAlgorithm_t<I, A>
    {
    private:
      typedef typename I::depth_t D;
          
    protected:
      D pixelOp(D pixel[A]) const
      {
        D result = std::abs(pixel[0]);
        for(unsigned int i=1; i < A; i++)
        {
          D temp = std::abs(pixel[i]);
          result = std::max(temp, result);
        }
        return result;
      }
    };
  }
}
#endif
