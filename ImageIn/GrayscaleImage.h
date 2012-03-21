#ifndef GRAYSCALEIMAGE_H
#define GRAYSCALEIMAGE_H

#include "Image.h"

namespace imagein
{
	/*!
     * \brief Class to manipulate grayscale Images.
     *
     * This class is a subclass of Image_t used to manipulate grayscale (1 channel) Images.
     *
	 * The actual work is still done by the method of Image_t. This class only provides specialized functions to use with grayscale Images, 
	 * but they only call the method of Image_t.
     *
	 * \sa Image_t
     * \tparam D the type of pixel values.
     */
    template <typename D>
    class GrayscaleImage_t : public Image_t<D>
    {
        public:
			
			/*!
             * \brief Default constructor. Constructs an image from the parameters given.
             *
			 * See Image_t default constructor for more information. For this type of image, the number of channels is always 1
             *
             * \param width The image width
             * \param height The image height
             * \param data The actual data matrix containing the pixels of the image.  No verification of the size of the array is performed.
			 *
             */
            GrayscaleImage_t(unsigned int width=0, unsigned int height=0, const D* data=NULL) : Image_t<D>(width, height, 1, data) {};
		
			/*!
             * \brief Constructs an image from the given file.
             *
             * See Image_t constructor for more information.
             *
             * \param filename The relative or absolute filename to the image file.
			 * \throw ImageFileException if the file format isn't supported or if there is an error while reading the file.
			 * \throw BadImageException if the file does not contains 1 channels. 
			 */
            GrayscaleImage_t(std::string filename);
		
			/*!
			 * \brief Copy constructor.
			 *
			 * \param other The Image to be copied.
			 */
            GrayscaleImage_t(const GrayscaleImage_t<D>& other) : Image_t<D>(other) {};
			
			/*!
             * \brief Crops the image to the boundaries defined by a Rectangle.
             *
             * \param rect the rectangle used to define the boundaries of the new image.
             * \return A new image of the same type.
             */
            GrayscaleImage_t<D>* crop(const Rectangle& rect) const;
			
			//! accessor to the value of a pixel. 
            inline const D& getPixel(unsigned int x, unsigned int y) const { return Image_t<D>::getPixel(x, y, 0); }
			
			//! mutator for the value of a pixel. 
            inline void setPixel(unsigned int x, unsigned int y, const D& cPixel) { Image_t<D>::setPixel(x, y, 0, cPixel); };
			
			//! Returns the histogram of the image.
            Histogram getHistogram(const Rectangle& rect = Rectangle()) const { return Image_t<D>::getHistogram(0, rect); };

            virtual ~GrayscaleImage_t() {};
    };

    typedef GrayscaleImage_t<depth8_t> GrayscaleImage_8; //!< 8 bits depth grayscale image
    typedef GrayscaleImage_t<depth16_t> GrayscaleImage_16; //!< 16 bits depth grayscale image
    typedef GrayscaleImage_t<depth32_t> GrayscaleImage_32; //!< 32 bits depth grayscale image
    typedef GrayscaleImage_t<depth_default_t> GrayscaleImage; //!< Standard Image is 8 bits depth
}

#include "GrayscaleImage.tpp"

#endif // GRAYSCALEIMAGE_H
