#ifndef GRAYSCALEIMAGE_H
#define GRAYSCALEIMAGE_H

#include "Image.h"


namespace imagein
{
    template <typename D>
    class GrayscaleImage : public Image<D>
    {
        public:
            GrayscaleImage(unsigned int width, unsigned int height, const D* data) : Image<D>(width, height, 1, data) {};
            GrayscaleImage(std::string filename);
            virtual ~GrayscaleImage();


            inline const D& getPixel(unsigned int x, unsigned int y) const { return Image<D>::getPixel(x, y, 0); }

            inline void setPixel(unsigned int x, unsigned int y, const D& cPixel) { Image<D>::setPixel(x, y, 0, cPixel); };

            Histogram getHistogram(const Rectangle& rect = Rectangle()) const { return Image<D>::getHistogram(0, rect); };

    };
}

#include "GrayscaleImage.tpp"

#endif // GRAYSCALEIMAGE_H
