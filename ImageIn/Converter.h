#ifndef CONVERTER_H
#define CONVERTER_H

#include "Image.h"
#include "GrayscaleImage.h"
#include "RgbImage.h"

#include <cmath>
#include <iostream>
#include <limits>

namespace imagein {

    /*!
     * \brief Trait class used to convert Image type.
     *
     * This class contains static methods used to convert an image from one imagein
     * type to another. All the content of this class is present in the specialization.
     */
    template <typename T>
    class Converter
    {
    };

    //! Converter to RgbImage_t (specialization)
    template <typename D>
    class Converter <RgbImage_t<D> > {
        public:
            /*!
             * \brief Converts GrayscaleImage to RgbImage.
             *
             * A new object is allocated. The 3 channels of the resulting image will be equal 
             * to the origin image.
             *
             * \param from The GrayscaleImage to convert.
             */
            static RgbImage_t<D>* convert(const GrayscaleImage_t<D>& from);

            /*!
             * \brief Converts RgbImage to RgbImage
             *
             * This method does nothing, but is necessary when you want a RgbImage from an unknown 
             * template parameter.
             *
             * \param from The RgbImage to convert.
             */
            static RgbImage_t<D>* convert(const RgbImage_t<D>& from);

            /*!
             * \brief Converts Image to RgbImage
             *
             * If the origin image has 1 or two channels, the first one is used for
             * all three channels of the resulting image.
             *
             * If the origin image has 3 or more channels, the first three channels are used
             * for the three channels of the resulting image.
             *
             * \param from The Image to convert.
             */
            static RgbImage_t<D>* convert(const Image_t<D>& from);
    };

    //! Converter to GrayscaleImage_t (specialization)
    template <typename D>
    class Converter <GrayscaleImage_t<D> > {
        public:

            /*!
             * \brief Converts GrayscaleImage to GrayscaleImage
             *
             * This method does nothing, but is necessary when you want a GrayscaleImage from an unknown 
             * template parameter.
             *
             * \param from The GrayscaleImage to convert.
             */
            static GrayscaleImage_t<D>* convert(const GrayscaleImage_t<D>& from);

            /*!
             * \brief Converts RgbImage to GrayscaleImage
             *
             * The resulting image is the arithmetic average of the three channels of the origin image.
             *
             * \param from The RgbImage to convert.
             */
            static GrayscaleImage_t<D>* convert(const RgbImage_t<D>& from);

            /*!
             * \brief Converts Image to GrayscaleImage
             *
             * If the origin image has 1 or 2 channels, the first one is used.
             *
             * If the origin image has 3 or more channels, the resulting image is the arithmetic average
             * of the first three channels.
             *
             * \param from The Image to convert.
             */
            static GrayscaleImage_t<D>* convert(const Image_t<D>& from);
    };
   
    //! Converter to Image_t (specialization)
    template <typename D>
    class Converter <Image_t<D> > {
        public:

            /*!
             * \brief Converts GrayscaleImage to Image
             *
             * As the class Image_t can contain every of its subclasses, no operation is performed on the data.
             *
             * \param from The GrayscaleImage to convert.
             */
            static Image_t<D>* convert(const GrayscaleImage_t<D>& from);

            /*!
             * \brief Converts RgbImage to Image
             *
             * As the class Image_t can contain every of its subclasses, no operation is performed on the data.
             *
             * \param from The GrayscaleImage to convert.
             */
            static Image_t<D>* convert(const RgbImage_t<D>& from);

            /*!
             * \brief Converts Image to Image
             *
             * As the class Image_t can contain every of its subclasses, no operation is performed on the data.
             *  
             * This method is useful when you want an Image from an unknown template parameter.
             *
             * \param from The Image to convert.
             */
            static Image_t<D>* convert(const Image_t<D>& from);

            /*!
             * \brief Converts Image to Image<int>
             *
             * As the class Image_t can contain every of its subclasses, no operation is performed on the data.
             *  
             * This method is useful for filtering for example.
             *
             * \param from The Image to convert.
             */
            static Image_t<int>* convertToInt(const Image_t<D>& from);
            
            /*!
             * \brief Converts Image to displayable Image
             *
             * Sometime an image can contains non-displayable values. This method make it displayable.
             *  
             * This method is useful when you want an Image displayable (after filtering).
             * 
             * \param from The Image to convert.
             */
            static Image_t<D>* makeDisplayable(const Image_t<int>& from);
            static Image_t<D>* makeDisplayable(const Image_t<bool>& from);
    };
}

#include "Converter.tpp"

#endif
