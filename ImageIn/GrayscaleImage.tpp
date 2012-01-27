//#include "GrayscaleImage.h"

template <typename D>
GrayscaleImage_t<D>* GrayscaleImage_t<D>::crop(const Rectangle& rect) const
{
    GrayscaleImage_t<D>* ret = new GrayscaleImage_t<D>(rect.w, rect.h);

    crop(rect, &(ret->_mat));

    return ret;
}

