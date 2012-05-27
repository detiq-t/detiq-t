//#incluDe "Image.h"

#include "ImageFile.h"
#include "ImageFileAbsFactory.h"

#include <stdexcept>

template <typename D>
imagein::Image_t<D>::Image_t(unsigned int width = 0, unsigned int height = 0, unsigned int nChannels=0, const D* data=NULL)
 : _width(width), _height(height), _nChannels(nChannels)
{
    _mat = new D[width * height * nChannels];
    if(data) {
        std::copy(data, data+(width * height * nChannels), _mat);
    }
}


template <typename D>
imagein::Image_t<D>::Image_t(std::string filename)
{
    imagein::ImageFile* im = imagein::ImageFileAbsFactory::getFactory()->getImageFile(filename);

    if(im==NULL) {
        throw "Unable to open file";
    }

    _width = im->readWidth();
    _height = im->readHeight();
    _nChannels = im->readNbChannels();
    _mat = reinterpret_cast<D*>(im->readData());

    delete im;
}

template <typename D>
imagein::Image_t<D>::Image_t(const imagein::Image_t<D>& other)
 : _width(other._width), _height(other._height), _nChannels(other._nChannels)
{
    _mat = new D[_width*_height*_nChannels];
    std::copy(other.begin(), other.end(), _mat);
}

template <typename D>
imagein::Image_t<D>::~Image_t()
{
    delete[] _mat;
}

template <typename D>
imagein::Image_t<D>& imagein::Image_t<D>::operator=(const imagein::Image_t<D>& other)
{
    if (this == &other) return *this; // handle self assignment

    this->_width = other._width;
    this->_height = other._height;
    this->_nChannels = other._nChannels;

    delete[] _mat;
    _mat = new D[_width*_height*_nChannels];
    std::copy(other.begin(), other.end(), _mat);

    return *this;
}

template <typename D>
const D& imagein::Image_t<D>::getPixel(unsigned int x, unsigned int y, unsigned int channel) const
{ 
	if(x >= _width || y >= _height || channel > _nChannels) {
        throw std::out_of_range("Invalid coordinates for getPixel");
    }
	
	return _mat[y*_nChannels*_width + x*_nChannels + channel]; 
}

template <typename D>
void imagein::Image_t<D>::setPixel(unsigned int x, unsigned int y, unsigned int channel, const D& cPixel)
{
    if(x >= _width || y >= _height || channel > _nChannels) {
        throw std::out_of_range("Invalid coordinates for setPixel");
    }

    _mat[y*_width*_nChannels + x*_nChannels + channel] = cPixel;
}

template <typename D>
void imagein::Image_t<D>::setPixel(unsigned int x, unsigned int y, const D* pixel)
{
    if(x >= _width || y >= _height) {
        throw std::out_of_range("Invalid coordinates for setPixel");
    }

    std::copy(pixel, pixel+_nChannels, _mat+y*_width*_nChannels+x*_nChannels);
}

template <typename D>
bool imagein::Image_t<D>::operator==(const imagein::Image_t<D>& img) const {
    if(this->_width != img._width) return false;
    if(this->_height != img._height) return false;
    if(this->_nChannels != img._nChannels) return false;
    for(const_iterator it = this->begin(), jt = img.begin(); it < this->end(); ++it, ++jt) {
        if(*it != *jt) return false;
    }
    return true;
}

template <typename D>
void imagein::Image_t<D>::save(const std::string& filename) const
{
    imagein::ImageFile* im = imagein::ImageFileAbsFactory::getFactory()->getImageFile(filename);

    im->writeData(reinterpret_cast<const char* const>(_mat), _width, _height, _nChannels, sizeof(D)*8);

    delete im;
}

template <typename D>
imagein::Image_t<D>* imagein::Image_t<D>::crop(const imagein::Rectangle& rect) const
{
    imagein::Image_t<D>* ret = new imagein::Image_t<D>(rect.w, rect.h, this->_nChannels);

    crop(rect, ret->_mat);

    return ret;
}

template <typename D>
void imagein::Image_t<D>::crop(const imagein::Rectangle& rect, D* mat) const
{
    unsigned int topleft = rect.y*_width*_nChannels + rect.x*_nChannels;
    unsigned int bottomright = (rect.y+rect.h-1)*_width*_nChannels + (rect.x+rect.w)*_nChannels;

    imagein::Image_t<D>::const_iterator it = this->begin() + topleft; //iterator pointing on the top-left corner of the rectangle
    imagein::Image_t<D>::const_iterator end = this->begin() + bottomright; //iterator pointing just after the bottom-right corner of the rectangle

    D* di = mat; //pointer to the first element of data

    unsigned int columnNo = 0;
    unsigned int channelNo = 0;

    while(it < end) {
        *di = *it;
        ++di;
        ++it;

        if(++channelNo == _nChannels) {
            ++columnNo;
            channelNo = 0;
        }

        if(columnNo == rect.w) {
            it += (_width-rect.w) * _nChannels;
            columnNo = 0;
            channelNo = 0;
        }
    }
}
