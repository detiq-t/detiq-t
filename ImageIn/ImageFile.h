#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <string>
#include "ImageFileException.h"

namespace imagein
{
    /*!
     * \brief This class is used to open an image file. The user of ImageIn should never have to use it directly, as it is used by Image's constructor/save methods.
     *
     * This class is abstract, and is an interface to concrete classes representing different image file formats (png, jpg...).
     * Every method writing or reading in a file will use classes implementing this interface, so that it can prepare its data regardless of the file format being used.
     *
     * To add a new format to ImageIn, follow these steps :
     * -# Create a class deriving from ImageFile and reimplement the methods defined in it.
     * -# Create a class deriving from ImageFileFactory and reimplement the method getImageFile() so that it can return your ImageFile class when it needs to
     * (don't forget to call the original getImageFileMethod so you dont remove Jpg, Png and Bmp support).
     * -# call the method ImageFileAbsFactory::setFactory(), passing an instance of your newly created factory class.
     *
     * The file format will then be available to use within the Image classes.
     *
     * \sa ImageFileFactory::getImageFile(), ImageFileAbsFactory::setFactory
     */
    class ImageFile
    {
        public:

            /*!
             * \brief enum representing the different file format that ImageIn is able to read/write
             */
            typedef enum {
                F_BMP,
                F_JPG,
                F_PNG,
                F_WEBP
            }Format;

            /*!
             * \brief Creates an ImageFile with given filename
             *
             * If the file exists, you will be able to overwrite it or read from it. If it doesn't, you will only be able to write (creating the file)
             * \param filename The absolute or relative filename to use.
             */
            ImageFile(std::string filename) : _filename(filename) {}

            /*!
             * \brief Standard virtual destructor.
             */
            virtual ~ImageFile() {};

            /*!
             * \brief Reads the height of the image from the file.
             *
             * \throw FileNotFoundException if the file doesn't exist.
             * \return the height of the image in pixels.
             */
            virtual unsigned int readHeight()=0;

            /*!
             * \brief Reads the width of the image from the file.
             *
             * \throw FileNotFoundException if the file doesn't exist.
             * \return the width of the image in pixels.
             */
            virtual unsigned int readWidth()=0;

            /*!
             * \brief Reads the number of channels of the image from the file.
             *
             * \throw FileNotFoundException if the file doesn't exist.
             * \return the number of channels of the image.
             */
            virtual unsigned int readNbChannels()=0;

            /*!
             * \brief Reads the size of a pixel (depth) from the file.
             *
             * \throw FileNotFoundException if the file doesn't exist.
             * \return the size of a pixel (in number of bits).
             */
            virtual unsigned int readDepth()=0;

            /*!
             * \brief Reads the image data from the file.
             *
             * The data is returned as an array of bytes (char). It must be converted (cast) to the appropriate format regarding the depth of a pixel.
             *
             * \throw FileNotFoundException if the file doesn't exist.
             * \return an array of char representing the image data.
             */
            virtual void* readData()=0;

            /*!
             * \brief Writes image data into a file.
             *
             * \param data The data to be written in the file (must be given as an array of bytes (char)).
             * \param width The width of the image
             * \param height The height of the image
             * \param nChannels The number of channels for each pixel.
             * \param depth The size (in bits) of the data in each value of a pixel. Must represent an integer number of bytes (8, 16, 24...)
             */
            virtual void writeData(const void* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)=0;

        protected:
            std::string _filename;
    };
}

#endif // IMAGEFILE_H
