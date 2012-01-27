#include "Histogram.h"

#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace imagein;

template <typename D>
Histogram::Histogram(const Image_t<D>& img, unsigned int channel, const Rectangle& rect) : Array(pow(2, sizeof(D)*8))
{

    for(unsigned int i=0; i<this->_width; i++) {
        this->_array[i] = 0;
    }
    unsigned int maxw = rect.w > 0 ? rect.w : img.getWidth();
    unsigned int maxh = rect.h > 0 ? rect.h : img.getHeight();
    for(unsigned int j=rect.y; j<maxh; j++) {
        for(unsigned int i=rect.x; i<maxw; i++) {
            D pixel = img.getPixel(i, j, channel);
            int value = pixel > 0 ? pixel : this->_width + pixel;
            this->_array[value]++;
        }
    }
}

template <typename D>
Histogram::Histogram(const Image_t<D>& img, const Rectangle& rect) : Array(pow(2, sizeof(D)))
{
    for(unsigned int i=0; i<this->_width; i++) {
        this->_array[i] = 0;
    }
    unsigned int maxw = rect.w > 0 ? rect.w : img.getWidth();
    unsigned int maxh = rect.h > 0 ? rect.h : img.getHeight();
    for(unsigned int j=rect.y; j<maxh; j++) {
        for(unsigned int i=rect.x; i<maxw; i++) {
            D pixel = img.getPixel(i, j, 0);
            int value = pixel > 0 ? pixel : this->_width + pixel;
            this->_array[value]++;
        }
    }
}

