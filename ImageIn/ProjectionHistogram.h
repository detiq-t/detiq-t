#ifndef PROJECTIONHISTOGRAM_H
#define PROJECTIONHISTOGRAM_H


#include "Array.h"
#include "Image.h"
#include <iostream>

namespace imagein
{
    /*!
     * \brief ProjectionHistogram creates the projection histogram of an Image from a given a value, the Rectangle where the projection applies, the direction of the projection and the channel that's projected
     *
     * This class is inherited from Array, therefore it's a fixed-size array of integers, the element with rank K of the array is the number of pixels of the given value on the Kth row/column of the Image (cropped from the Rectangle).
     */

    class ProjectionHistogram : public Array
    {
        public:
            template <typename D>
            ProjectionHistogram(const Image<D>& img, D value, bool horizontal, unsigned int channel, const Rectangle& rect);
            template <typename D>
            ProjectionHistogram(const Image<D>& img, D value, bool horizontal, const Rectangle& rect);
            inline virtual ~ProjectionHistogram() {};
        protected:
        private:
    };
}


#endif // PROJECTIONHISTOGRAM_H
