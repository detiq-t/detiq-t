//#include "Converter.h"

using namespace imagein;

template <typename D>
RgbImage_t<D>* Converter<RgbImage_t<D> >::convert(const GrayscaleImage_t<D>& from) 
{
    D* data = new D[from.getWidth() * from.getHeight() * 3];
    D* ptr = data;

    for(typename Image_t<D>::const_iterator it = from.begin() ; it != from.end() ; ++it) {
        *(ptr++) = *it;
        *(ptr++) = *it;
        *(ptr++) = *it;
    }

    return new RgbImage_t<D>(from.getWidth(), from.getHeight(), data);
}

template <typename D>
RgbImage_t<D>* Converter<RgbImage_t<D> >::convert(const RgbImage_t<D>& from)
{
    return new RgbImage_t<D>(from.getWidth(), from.getHeight(), from.begin());
}

template <typename D>
RgbImage_t<D>* Converter<RgbImage_t<D> >::convert(const Image_t<D>& from) 
{
    D* data = new D[from.getWidth() * from.getHeight() * 3];
    D* ptr = data;

    if (from.getNbChannels() < 3) {
        for(int j = 0 ; j < from.getHeight() ; ++j) {
            for(int i = 0 ; i < from.getWidth() ; ++i) {
                *(ptr++) = from.getPixel(i, j, 0);
                *(ptr++) = from.getPixel(i, j, 0);
                *(ptr++) = from.getPixel(i, j, 0);
            }
        }
    }
    else {
        for(int j = 0 ; j < from.getHeight() ; ++j) {
            for(int i = 0 ; i < from.getWidth() ; ++i) {
                *(ptr++) = from.getPixel(i, j, 0);
                *(ptr++) = from.getPixel(i, j, 1);
                *(ptr++) = from.getPixel(i, j, 2);
            }
        }
    }

    return new RgbImage_t<D>(from.getWidth(), from.getHeight(), data);
}

template <typename D>
GrayscaleImage_t<D>* Converter<GrayscaleImage_t<D> >::convert(const GrayscaleImage_t<D>& from)
{
    return new GrayscaleImage_t<D>(from.getWidth(), from.getHeight(), from.begin());
}

template <typename D>
GrayscaleImage_t<D>* Converter<GrayscaleImage_t<D> >::convert(const RgbImage_t<D>& from) 
{
    D* data = new D[from.getWidth() * from.getHeight()];
    D* ptr = data;

    for(int j = 0 ; j < from.getHeight() ; ++j) {
        for(int i = 0 ; i < from.getWidth() ; ++i) {
            *(ptr++) = 
                ( from.getPixel(i, j, 0) + 
                  from.getPixel(i, j, 1) + 
                  from.getPixel(i, j, 2)
                ) / 3;
        }
    }

    return new GrayscaleImage_t<D>(from.getWidth(), from.getHeight(), data);
}

template <typename D>
GrayscaleImage_t<D>* Converter<GrayscaleImage_t<D> >::convert(const Image_t<D>& from) 
{
    D* data = new D[from.getWidth() * from.getHeight()];
    D* ptr = data;

    if (from.getNbChannels() < 3) {
        for(int j = 0 ; j < from.getHeight() ; ++j) {
            for(int i = 0 ; i < from.getWidth() ; ++i) {
                *(ptr++) = from.getPixel(i, j, 0);
            }
        }
    }
    else {
        for(int j = 0 ; j < from.getHeight() ; ++j) {
            for(int i = 0 ; i < from.getWidth() ; ++i) {
                *(ptr++) = 
                    ( from.getPixel(i, j, 0) + 
                      from.getPixel(i, j, 1) + 
                      from.getPixel(i, j, 2)
                    ) / 3;
            }
        }
    }

    return new GrayscaleImage(from.getWidth(), from.getHeight(), data);
}

template <typename D>
Image_t<D>* Converter<Image_t<D> >::convert(const GrayscaleImage_t<D>& from)
{
    return new Image_t<D>(from.getWidth(), from.getHeight(), 1, from.begin());
}

template <typename D>
Image_t<D>* Converter<Image_t<D> >::convert(const RgbImage_t<D>& from)
{
    return new Image_t<D>(from.getWidth(), from.getHeight(), 3, from.begin());
}

template <typename D>
Image_t<D>* Converter<Image_t<D> >::convert(const Image_t<D>& from)
{
    return new Image_t<D>(from.getWidth(), from.getHeight(), from.getNbChannels(), from.begin());
}
