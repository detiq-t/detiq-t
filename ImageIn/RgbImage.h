#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include "stdint.h"

#include "Image.h"

namespace imagein
{
    template <typename D>
    class RgbImage_t : public Image_t<D>
    {
        public:
            RgbImage_t(unsigned int width=0, unsigned int height=0, D* data=NULL) : Image_t<D>(width, height, 3, data) {};
            RgbImage_t(std::string filename);
            RgbImage_t(const RgbImage_t<D>& other) : Image_t<D>(other) {};

            RgbImage_t<D>* crop(const Rectangle& rect) const;

            inline const D& getRed(unsigned int x, unsigned int y) const { return Image_t<D>::getPixel(x, y, 0); }
            inline const D& getGreen(unsigned int x, unsigned int y) const { return Image_t<D>::getPixel(x, y, 1); }
            inline const D& getBlue(unsigned int x, unsigned int y) const { return Image_t<D>::getPixel(x, y, 2); }

            inline void setRed(unsigned int x, unsigned int y, const D& cPixel) { Image_t<D>::setPixel(x, y, 0, cPixel); }
            inline void setGreen(unsigned int x, unsigned int y, const D& cPixel) { Image_t<D>::setPixel(x, y, 1, cPixel); }
            inline void setBlue(unsigned int x, unsigned int y, const D& cPixel) { Image_t<D>::setPixel(x, y, 2, cPixel); }

            virtual ~RgbImage_t() {};
    };

    typedef RgbImage_t<uint8_t> RgbImage_8; //!< 8 bits depth RGB Image.
    typedef RgbImage_8 RgbImage; //!< Standard Image is 8 bits depth
}

#include "RgbImage.tpp"

#endif // RGBIMAGE_H
