//#include "GrayscaleImage.h"

#include "BadImageException.h"

template <typename D>
imagein::GrayscaleImage_t<D>::GrayscaleImage_t(std::string filename) 
 : imagein::Image_t<D>(filename)
{
    if(this->_nChannels != 1) 
        throw BadImageException("Image with 1 channels expected", __LINE__, __FILE__);
}

template <typename D>
imagein::GrayscaleImage_t<D>* imagein::GrayscaleImage_t<D>::crop(const imagein::Rectangle& rect) const
{
    imagein::GrayscaleImage_t<D>* ret = new imagein::GrayscaleImage_t<D>(rect.w, rect.h);

    Image_t<D>::crop(rect, ret->_mat);

    return ret;
}

