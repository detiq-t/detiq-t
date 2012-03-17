//#include "RgbImage.h"

#include "BadImageException.h"

template <typename D>
imagein::RgbImage_t<D>::RgbImage_t(std::string filename)
 : imagein::Image_t<D>(filename)
{
    if(this->_nChannels != 3) 
        throw BadImageException("Image with 3 channels expected", __LINE__, __FILE__);
}

template <typename D>
imagein::RgbImage_t<D>* imagein::RgbImage_t<D>::crop(const Rectangle& rect) const
{
    RgbImage_t<D>* ret = new RgbImage_t<D>(rect.w, rect.h);

    Image_t<D>::crop(rect, ret->_mat);

    return ret;
}
