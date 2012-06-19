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

#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Array.h"
#include "Rectangle.h"


namespace imagein
{
    template <typename D>
    class Image_t;
	
    /*!
     * \brief This class is used to represent Image Histograms.
     *
     * This class inherits Array, therefore it's a fixed-size array of integers, the element with rank K of the array is the number of pixels of the given value on the Kth row/column of the Image (cropped from the Rectangle).
     */
    class Histogram : public Array<unsigned int>
    {
            
         public:
        /*!
         * \brief Constructs an Histogram from an image.
         *
         * \param img The image from which to compute the histogram.
         * \param channel The channel to consider for the values.
         * \param rect A rectangle used to crop the image before computing the Histogram.
         */
          template <typename D>
          Histogram(const Image_t<D>& img, unsigned int channel, const Rectangle& rect = Rectangle());
		
        /*!
         * \brief Constructs an Histogram from an image.
         *
         * \param img The image from which to compute the histogram.
         * \param rect A rectangle used to crop the image before computing the Histogram.
         */
          template <typename D>
          Histogram(const Image_t<D>& img, const Rectangle& rect = Rectangle());

          private:

          template<typename D>
          void computeHistogram(const Image_t<D>& img, unsigned int channel, const Rectangle& rect);
    };
}

#include "Histogram.tpp"

#endif // HISTOGRAM_H
