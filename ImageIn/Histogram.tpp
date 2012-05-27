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
