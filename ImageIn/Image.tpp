#include "Image.h"

#include "ImageFile.h"
#include "ImageFileFactory.h"

#include <stdexcept>

using namespace imagein;

template <typename D>
Image<D>::Image(std::string filename)
{
    ImageFile* im = ImageFileFactory::getImageFile(filename);

    _width = im->readWidth();
    _height = im->readHeight();
    _nChannels = im->readNbChannels();
    _mat = reinterpret_cast<D*>(im->readData());

    delete im;
}

template <typename D>
Image<D>::Image(const Image& other)
 : _width(other._width), _height(other._height), _nChannels(other._nChannels), _mat(other._mat)
{
}

template <typename D>
Image<D>& Image<D>::operator=(const Image& other)
{
    if (this == &other) return *this; // handle self assignment

    this->_width = other._width;
    this->_height = other._height;
    this->_nChannels = other._nChannels;
    this->_mat = other._mat;

    return *this;
}

template <typename D>
Image<D> Image<D>::clone()
{
    D* data = new D[_width*_height*_nChannels];

    std::copy(this->begin(), this->end(), data);

    return Image(_width, _height, _nChannels, data);
}

template <typename D>
void Image<D>::setPixel(unsigned int x, unsigned int y, unsigned int channel, const D& cPixel)
{
    if(x >= _width || y >= _height || channel > _nChannels) {
        throw std::out_of_range("Invalid coordinates for setPixel");
    }

    _mat[y*_width*_nChannels + x*_nChannels + channel] = cPixel;
}

template <typename D>
void Image<D>::setPixel(unsigned int x, unsigned int y, const D* pixel)
{
    if(x >= _width || y >= _height) {
        throw std::out_of_range("Invalid coordinates for setPixel");
    }

    std::copy(pixel, pixel+_nChannels, _mat+y*_width*_nChannels+x*_nChannels);
}

template<typename D>
Image<D> Image<D>::crop(const Rectangle& rect) const
{
    unsigned int topleft = rect.y*_width + rect.x;

    Image<D>::const_iterator it = this->begin() + topleft*_nChannels; //iterator pointing on the top-left corner of the rectangle
    Image<D>::const_iterator end = it + ((rect.h-1)*_width + rect.w)*_nChannels; //iterator pointing just after the bottom-right corner of the rectangle

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
    Image<D> ret;
    ret._width = rect.w;
    ret._height = rect.h;
    ret._nChannels = this->_nChannels;
    ret._mat = data;

    return ret;
}

template <typename D>
void Image<D>::save(const std::string& filename) const
{
    ImageFile* im = ImageFileFactory::getImageFile(filename);

    im->writeData(reinterpret_cast<char*>(_mat), _width, _height, _nChannels, sizeof(D));
}
