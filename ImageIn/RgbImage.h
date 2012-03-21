#ifndef RGBIMAGE_H
#define RGBIMAGE_H

#include "stdint.h"

#include "Image.h"

namespace imagein
{
	/*!
     * \brief Class to manipulate RGB Images.
     *
     * This class is a subclass of Image_t used to manipulate RGB (3 channels) Images.
     *
	 * The actual work is still done by the method of Image_t. This class only provides specialized functions to use with RGB Images, 
	 * but they only call the method of Image_t.
     *
	 * \see Image_t
     * \tparam D the type of pixel values.
     */
    template <typename D>
    class RgbImage_t : public Image_t<D>
    {
        public:
			
			/*!
             * \brief Default constructor. Constructs an image from the parameters given.
             *
			 * See Image_t default constructor for more information. For this type of image, the number of channels is always 3
             *
             * \param width The image width
             * \param height The image height
             * \param data The actual data matrix containing the pixels of the image.  No verification of the size of the array is performed.
			 *
             */
            RgbImage_t(unsigned int width=0, unsigned int height=0, const D* data=NULL) : Image_t<D>(width, height, 3, data) {};
		
			/*!
             * \brief Constructs an image from the given file.
             *
             * See Image_t constructor for more information.
             *
             * \param filename The relative or absolute filename to the image file.
			 * \throw ImageFileException if the file format isn't supported or if there is an error while reading the file.
			 * \throw BadImageException if the file does not contains 3 channels. 
			 */
            RgbImage_t(std::string filename);
		
			/*!
			 * \brief Copy constructor.
			 *
			 * \param other The Image to be copied.
			 */
            RgbImage_t(const RgbImage_t<D>& other) : Image_t<D>(other) {};
			
			/*!
             * \brief Crops the image to the boundaries defined by a Rectangle.
             *
             * \param rect the rectangle used to define the boundaries of the new image.
             * \return A new image of the same type.
             */
            RgbImage_t<D>* crop(const Rectangle& rect) const;
			
			//! Accessor to the first channel (red) of a pixel.
            inline const D& getRed(unsigned int x, unsigned int y) const { return Image_t<D>::getPixel(x, y, 0); }
            //! Accessor to the second channel (green) of a pixel.
			inline const D& getGreen(unsigned int x, unsigned int y) const { return Image_t<D>::getPixel(x, y, 1); }
			//! Accessor to the third channel (blue) of a pixel.
            inline const D& getBlue(unsigned int x, unsigned int y) const { return Image_t<D>::getPixel(x, y, 2); }

			//! Mutator for the first channel (red) of a pixel.
            inline void setRed(unsigned int x, unsigned int y, const D& cPixel) { Image_t<D>::setPixel(x, y, 0, cPixel); }
			//! Mutator for the second channel (green) of a pixel.
            inline void setGreen(unsigned int x, unsigned int y, const D& cPixel) { Image_t<D>::setPixel(x, y, 1, cPixel); }
			//! Mutator for the third channel (blue) of a pixel.
            inline void setBlue(unsigned int x, unsigned int y, const D& cPixel) { Image_t<D>::setPixel(x, y, 2, cPixel); }

            virtual ~RgbImage_t() {};
    };

    typedef RgbImage_t<depth8_t> RgbImage_8; //!< 8 bits depth RGB Image.
    typedef RgbImage_t<depth16_t> RgbImage_16; //!< 16 bits depth RGB Image.
    typedef RgbImage_t<depth32_t> RgbImage_32; //!< 32 bits depth RGB Image.
    typedef RgbImage_t<depth_default_t> RgbImage; //!< Standard Image is 8 bits depth
}

#include "RgbImage.tpp"

#endif // RGBIMAGE_H
