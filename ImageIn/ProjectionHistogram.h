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
	template <typename D>
    class ProjectionHistogram : public Array
    {
        public:
            ProjectionHistogram(const Image_t<D>& img, D value, bool horizontal, const Rectangle& rect, unsigned int channel = 0);
            ProjectionHistogram(const Image_t<D>& img, D value, bool horizontal, unsigned int channel = 0);
            inline virtual ~ProjectionHistogram() {};
        protected:
        private:
    };
}

#include "ProjectionHistogram.tpp"

#endif // PROJECTIONHISTOGRAM_H
