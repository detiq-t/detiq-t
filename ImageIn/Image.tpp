#include "Image.h"

using namespace ImageIn;

template<typename D>
Image<D>::Image(unsigned int width, unsigned int height, unsigned int nChannels, const D* data)
{

}

template<typename D>
Image<D>::Image(std::string filename)
{

}

template <typename D>
Image<D>::Image(const Image& other)
{
    //copy ctor
}

template <typename D>
Image<D>& Image<D>::operator=(const Image& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    //assignment operator

    return *this;
}

template <typename D>
const D& Image<D>::getPixel(unsigned int x, unsigned int y, unsigned int channel) const
{

}

template <typename D>
void Image<D>::setPixel(unsigned int x, unsigned int y, unsigned int channel, const D& cPixel)
{

}

template <typename D>
void Image<D>::setPixel(unsigned int x, unsigned int y, const D* pixel)
{

}

template<typename D>
Image<D> Image<D>::crop(const Rectangle& rect) const
{
    unsigned int topleft = rect.y*_width + rect.x;

    Image<D>::iterator it = this->begin() + topleft*_nChannels; //iterator pointing on the top-left corner of the rectangle
    Image<D>::iterator end = it + ((rect.h-1)*_width + rect.w)*_nChannels; //iterator pointing just after the bottom-right corner of the rectangle

    D* data = new D[rect.w * rect.y * _nChannels]; //new array containing the new image data
    D* di = data; //pointer to the first element of data

    unsigned int columnNo = 0;

    while(it < end) {
        *di = *it;
        ++di;
        ++it;

        if(++columnNo == rect.w) {
            it += (_width-rect.w) * _nChannels;
            columnNo = 0;
        }
    }

    //creating an empty image then filling its attributes manually avoids a copy of every value in the data array.
    Image<D> ret();
    ret._width = rect.w;
    ret._height = rect.h;
    ret._nChannels = this->_nChannels;
    ret._mat = data;

    return ret;
}

template<typename D>
void Image<D>::save(std::string filename, ImgFormat format) const
{

}
