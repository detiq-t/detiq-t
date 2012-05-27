#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include "mystdint.h"

#include "Rectangle.h"
#include "Histogram.h"

namespace imagein
{
    /*!
     * \brief Main class to manipulate images.
     *
     * The Image_t class is used to manipulate matrix images. It can handle any type of 2D image, and the
     * subclasses are only simplified interfaces for this class. If you don't know which type of image
     * you are dealing with, you can always use this class.
     *
     * The depth of the image is set using the template parameter. The most common depth
     * is 8 bits (1 byte) so you can use unsigned char as the template parameter. If you want
     * to use a 32-bit depth grayscale image, you can use uint32_t. These are only examples
     * and you can use whatever numeric type you wish as long as they are basic c++ types (with operator sizeof working).
     * Note that if you use  non-standard types, some algorithms may not work with this type of image.
     *
     * \tparam D the type of pixel values.
     */
    template <typename D>
    class Image_t
    {
        public:
            typedef D depth_t;
            typedef D* iterator; //!< Random access iterator
            typedef const D* const_iterator; //!< Random access const-iterator

            /*!
             * \brief Default constructor. Constructs an image from the parameters given.
             *
             * As the dimensions of an image are constant, creating an empty image is only useful when you plan to use the affectation constructor later.
             * It is only provided so that you can use Images C arrays.
             *
             * \param width The image width
             * \param height The image height
             * \param nChannels The number of channels of the image.
             * \param data The actual data matrix containing the pixels of the image.  No verification of the size of the array is performed.
             */
            Image_t(unsigned int width, unsigned int height, unsigned int nChannels, const D* data);
            
			/*!
             * \brief Constructs an image from the given file.
             *
             * The file format currently supported are jpg, png, bmp. Other formats will raise an exception.
             *
             * If you want to use other file formats, see the class ImageFile and ImageFileFactory for instructions.
             *
             * \param filename The relative or absolute filename to the image file.
             * \throw ImageFileException if the file format isn't supported or if there is an error while reading the file.
             */
            Image_t(std::string filename);

            /*!
             * \brief Image destructor.
             *
             * The data matrix is deleted when the image is deleted. You should be careful if the data
             * is still accessible from outside the class.
             */
            virtual ~Image_t();

            /*!
             * \brief Copy constructor
             *
             * \param other The image to be copied.
             */
            Image_t(const Image_t& other);

            /*!
             * \brief Affect operator.
             *
             * \param other The image to be affected.
             * \sa Image(const Image_t<D>& other)
             */
            Image_t<D>& operator=(const Image_t& other);

            //! Returns the width of the image
            inline unsigned int getWidth() const { return _width; };
            //! Returns the height of the image
            inline unsigned int getHeight() const { return _height; };
            //! Returns the number of channels of the image
            inline unsigned int getNbChannels() const { return _nChannels; };

            /*!
             * \brief Returns the value of a pixel.
             *
             * The origin of the coordinates system is in the top-left corner of the image.
             *
             * \param x The abscissa of the pixel
             * \param y The ordinate of the pixel
             * \param channel The channel of the value that will be returned.
             * \return The value contained in the matrix at the given coordinates.
             * \throw out_of_range if the parameters are not a valid pixel.
             */
            inline const D& getPixel(unsigned int x, unsigned int y, unsigned int channel) const;

            /*!
             * \brief Set the value of a channel for the given pixel.
             *
             * \param x The abscissa of the pixel
             * \param y The ordinate of the pixel
             * \param channel The channel to change.
             * \param cPixel The new value.
             * \throw out_of_range if the parameters are not a valid pixel.
             */
            inline void setPixel(unsigned int x, unsigned int y, unsigned int channel, const D& cPixel);

             /*!
             * \brief Set the values of the given pixel.
             *
             * \param x The abscissa of the pixel
             * \param y The ordinate of the pixel
             * \param pixel An array containing the values of each channels.
             * \throw out_of_range if the parameters are not a valid pixel.
             */
            void setPixel(unsigned int x, unsigned int y, const D* pixel);

            //! Returns an iterator to the first channel on the top-left corner of the image
            inline iterator begin() { return _mat; };
            //! Returns a const iterator to the first channel on the top-left corner of the image
            inline const_iterator begin() const { return _mat; };
            //! Returns an iterator past then end of the image
            inline iterator end() { return _mat + _width*_height*_nChannels; };
            //! returns a const iterator past the end of the image
            inline const_iterator end() const { return _mat + _width*_height*_nChannels; };
            inline unsigned int size() const { return _width*_height*_nChannels; };
            bool operator==(const imagein::Image_t<D>& img) const;

            /*!
             * \brief Saves the image into a file.
             *
             * The format of the image will be based on the filename extension.
             *
             * \param filename The filename to save the image to. If it exists, the content of the file will be replaced.
             */
            void save(const std::string& filename) const;

            /*!
             * \brief Returns the histogram of the image.
             *
             * \param channel The channel to take into account for the histogram.
             * \param rect The image area on which to calculate the Histogram.
             */
            inline Histogram getHistogram(unsigned int channel=0, const Rectangle& rect = Rectangle()) const { return Histogram(*this, channel, rect); };


            /*!
             * \brief Crops the image to the boundaries defined by a Rectangle.
             *
             * \param rect the rectangle used to define the boundaries of the new image.
             * \return A new image of the same type.
             */
            virtual Image_t<D>* crop(const Rectangle& rect) const;

        protected:
            void crop(const Rectangle& rect, D* mat) const;

            unsigned int _width;
            unsigned int _height;
            unsigned int _nChannels;
            D* _mat;
    };
    
    typedef uint8_t depth8_t;
    typedef uint16_t depth16_t;
    typedef uint32_t depth32_t;
    typedef depth8_t depth_default_t;

    typedef Image_t<depth8_t> Image_8; //!< 8 bits depth Image. Provided for convenience.
    typedef Image_t<depth16_t> Image_16; //!< 8 bits depth Image. Provided for convenience.
    typedef Image_t<depth32_t> Image_32; //!< 8 bits depth Image. Provided for convenience.
    typedef Image_t<depth_default_t> Image; //!< Standard Image is 8 bits depth.
}

#include "Image.tpp"

#endif // IMAGE_H
