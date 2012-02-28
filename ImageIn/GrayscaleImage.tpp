//#include "GrayscaleImage.h"

#include "BadImageException.h"

template <typename D>
GrayscaleImage_t<D>::GrayscaleImage_t(std::string filename) 
 : Image_t<D>(filename)
{
    if(this->_nChannels != 1) 
        throw BadImageException("Image with 1 channels expected", __LINE__, __FILE__);
}

template <typename D>
GrayscaleImage_t<D>* GrayscaleImage_t<D>::crop(const Rectangle& rect) const
{
    GrayscaleImage_t<D>* ret = new GrayscaleImage_t<D>(rect.w, rect.h);

    crop(rect, ret->_mat);

    return ret;
}

