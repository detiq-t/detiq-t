#ifndef CONVERTER_H
#define CONVERTER_H

#include "Image.h"
#include "GrayscaleImage.h"
#include "RgbImage.h"

namespace imagein {
    template <typename T>
    class Converter
    {
    };

    template <typename D>
    class Converter <RgbImage_t<D> > {
        public:
            static RgbImage_t<D>* convert(const GrayscaleImage_t<D>& from);
            static RgbImage_t<D>* convert(const RgbImage_t<D>& from);
            static RgbImage_t<D>* convert(const Image_t<D>& from);
    };

    template <typename D>
    class Converter <GrayscaleImage_t<D> > {
        public:
            static GrayscaleImage_t<D>* convert(const GrayscaleImage_t<D>& from);
            static GrayscaleImage_t<D>* convert(const RgbImage_t<D>& from);
            static GrayscaleImage_t<D>* convert(const Image_t<D>& from);
    };
    
    template <typename D>
    class Converter <Image_t<D> > {
        public:
            static Image_t<D>* convert(const GrayscaleImage_t<D>& from);
            static Image_t<D>* convert(const RgbImage_t<D>& from);
            static Image_t<D>* convert(const Image_t<D>& from);
    };
}

#include "Converter.tpp"

#endif
