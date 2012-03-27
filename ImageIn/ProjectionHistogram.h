#ifndef PROJECTIONHISTOGRAM_H
#define PROJECTIONHISTOGRAM_H


#include "Array.h"
#include "Image.h"
#include <iostream>

namespace imagein
{
    /*!
     * \brief ProjectionHistogram_t creates the projection histogram of an Image from a given a value, the Rectangle where the projection applies, the direction of the projection and the channel that's projected
     *
     * This class is inherited from Array, therefore it's a fixed-size array of integers, the element with rank K of the array is the number of pixels of the given value on the Kth row/column of the Image (cropped from the Rectangle).
     */
	template <typename D>
    class ProjectionHistogram_t : public Array<unsigned int>
    {
        public:
			/*!
			 * \brief Constructs a ProjectionHistogram_t from an image.
			 *
			 * \param img The image from which to compute the projection histogram.
			 * \param value The value that will be counted.
			 * \param horizontal The projection histogram will count the pixels of the selected value for each row if true, for each column if false.
			 * \param rect A rectangle used to crop the image before computing the Histogram.
			 * \param channel The channel to consider for the values. Default value is 0 in case of a one channel image.
			 */
            ProjectionHistogram_t(const Image_t<D>& img, D value, bool horizontal, const Rectangle& rect, unsigned int channel = 0);
			
			/*!
			 * \brief Constructs a ProjectionHistogram_t from an image.
			 *
			 * \param img The image from which to compute the projection histogram.
			 * \param value The value that will be counted.
			 * \param horizontal The projection histogram will count the pixels of the selected value for each row if true, for each column if false.
			 * \param channel The channel to consider for the values. Default value is 0 in case of a one channel image.
			 */
            ProjectionHistogram_t(const Image_t<D>& img, D value, bool horizontal, unsigned int channel = 0);
			
			/*!
			 * \brief Classical destructor for ProjectionHistogram_t.
			 */
            inline virtual ~ProjectionHistogram_t() {};
    };

    typedef ProjectionHistogram_t<depth8_t> ProjectionHistogram_8; //!< 8 bits depth Projection Histogram. Provided for convenience.
    typedef ProjectionHistogram_t<depth16_t> ProjectionHistogram_16; //!< 16 bits depth Projection Histogram. Provided for convenience.
    typedef ProjectionHistogram_t<depth32_t> ProjectionHistogram_32; //!< 32 bits depth Projection Histogram. Provided for convenience.
    typedef ProjectionHistogram_t<depth_default_t> ProjectionHistogram; //!< Standard Projection Histogram is depth_t bits depth.
}

#include "ProjectionHistogram.tpp"

#endif // PROJECTIONHISTOGRAM_H
