//#include "RgbImage.h"

template <typename D>
RgbImage_t<D>* RgbImage_t<D>::crop(const Rectangle& rect) const
{
    RgbImage_t<D>* ret = new RgbImage_t<D>(rect.w, rect.h);

    Image_t<D>::crop(rect, &(ret->_mat));

    return ret;
}
