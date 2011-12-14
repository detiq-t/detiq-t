#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include "Image.h"


namespace imagein
{
    template <typename D>
    class RgbImage : Image<D>
    {
        public:
            RgbImage(unsigned int width, unsigned int height, const D* data) : Image<D>(width, height, 3, data) {};
            RgbImage(std::string filename);

            inline const D& getRed(unsigned int x, unsigned int y) const { return Image<D>::getPixel(x, y, 0); }
            inline const D& getGreen(unsigned int x, unsigned int y) const { return Image<D>::getPixel(x, y, 1); }
            inline const D& getBlue(unsigned int x, unsigned int y) const { return Image<D>::getPixel(x, y, 2); }

            inline void setRed(unsigned int x, unsigned int y, const D& cPixel) { Image<D>::setPixel(x, y, 0, cPixel); }
            inline void setGreen(unsigned int x, unsigned int y, const D& cPixel) { Image<D>::setPixel(x, y, 1, cPixel); }
            inline void setBlue(unsigned int x, unsigned int y, const D& cPixel) { Image<D>::setPixel(x, y, 2, cPixel); }

            virtual ~RgbImage();
    };
}

#include "RgbImage.tpp"

#endif // RGBIMAGE_H
