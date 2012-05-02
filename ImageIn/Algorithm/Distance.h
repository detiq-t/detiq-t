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
