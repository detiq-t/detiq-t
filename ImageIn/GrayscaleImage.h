#ifndef GRAYSCALEIMAGE_H
#define GRAYSCALEIMAGE_H

#include "Image.h"


namespace imagein
{
    template <typename D>
    class GrayscaleImage_t : public Image_t<D>
    {
        public:
            GrayscaleImage_t(unsigned int width=0, unsigned int height=0, D* data=NULL) : Image_t<D>(width, height, 1, data) {};
            GrayscaleImage_t(std::string filename);
            GrayscaleImage_t(const GrayscaleImage_t<D>& other) : Image_t<D>(other) {};

            GrayscaleImage_t<D>* crop(const Rectangle& rect) const;

            inline const D& getPixel(unsigned int x, unsigned int y) const { return Image_t<D>::getPixel(x, y, 0); }

            inline void setPixel(unsigned int x, unsigned int y, const D& cPixel) { Image_t<D>::setPixel(x, y, 0, cPixel); };

            Histogram getHistogram(const Rectangle& rect = Rectangle()) const { return Image_t<D>::getHistogram(0, rect); };

            virtual ~GrayscaleImage_t() {};
    };

    typedef GrayscaleImage_t<unsigned char> GrayscaleImage_8; //!< 8 bits depth grayscale image
    typedef GrayscaleImage_t<unsigned short> GrayscaleImage_16; //!< 16 bits depth grayscale image
    typedef GrayscaleImage_8 GrayscaleImage; //!< Standard Image is 8 bits depth
}

#include "GrayscaleImage.tpp"

#endif // GRAYSCALEIMAGE_H
