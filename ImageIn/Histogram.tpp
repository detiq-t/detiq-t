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

#include "Histogram.h"

#include <cmath>
#include <iostream>
#include <cstdlib>

template <typename D>
imagein::Histogram::Histogram(const imagein::Image_t<D>& img, unsigned int channel, const imagein::Rectangle& rect) : imagein::Array<unsigned int>(1 << (sizeof(D)*8))
{
    this->computeHistogram(img, channel, rect);
}

template <typename D>
imagein::Histogram::Histogram(const imagein::Image_t<D>& img, const imagein::Rectangle& rect) : imagein::Array<unsigned int>(1 << (sizeof(D)*8))
{
    this->computeHistogram(img, 0, rect);
}

template<typename D>
void imagein::Histogram::computeHistogram(const Image_t<D>& img, unsigned int channel, const Rectangle& rect)
{
    for(unsigned int i=0; i<this->_width; i++) {
        this->_array[i] = 0;
    }
    unsigned int maxw = rect.w > 0 ? rect.x+rect.w : img.getWidth();
    unsigned int maxh = rect.h > 0 ? rect.y+rect.h : img.getHeight();
	
    for(unsigned int j=rect.y; j<maxh; j++) {
        for(unsigned int i=rect.x; i<maxw; i++) {
            D pixel = img.getPixel(i, j, channel);
            //unsigned int value = pixel >= 0 ? pixel : this->_width + pixel;
            this->_array[static_cast<unsigned int>(pixel)]++;
        }
    }
}
