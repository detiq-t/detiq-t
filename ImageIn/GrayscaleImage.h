#ifndef GRAYSCALEIMAGE_H
#define GRAYSCALEIMAGE_H

#include "Image.h"


namespace imagein
{
    template <typename D>
    class GrayscaleImage : public Image<D>
    {
        public:
            GrayscaleImage(unsigned int width, unsigned int height, D* data) : Image<D>(width, height, 1, data) {};
            GrayscaleImage(std::string filename);
            virtual ~GrayscaleImage();


            inline const D& getPixel(unsigned int x, unsigned int y) const { return Image<D>::getPixel(x, y, 0); }

            inline void setPixel(unsigned int x, unsigned int y, const D& cPixel) { Image<D>::setPixel(x, y, 0, cPixel); };

            Histogram getHistogram(const Rectangle& rect = Rectangle()) const { return Image<D>::getHistogram(0, rect); };

    };

    typedef GrayscaleImage<unsigned char> GrayscaleImage_8; //!< 8 bits depth grayscale image
    typedef GrayscaleImage<unsigned int> GrayscaleImage_32; //!< 32 bits depth grayscale image
}

#include "GrayscaleImage.tpp"

#endif // GRAYSCALEIMAGE_H
