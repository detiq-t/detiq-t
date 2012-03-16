#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include "ImageFile.h"

#include <iostream>
#include <fstream>

#include <png.h>

namespace imagein
{
	//! ImageFile subclass for PNG files. See ImageFile for details.
    class PngImage : public ImageFile
    {
        public:
            PngImage(std::string filename);

            ~PngImage();

            inline unsigned int readHeight();
            inline unsigned int readWidth();
            inline unsigned int readNbChannels();
            inline unsigned int readDepth();

            void* readData();

            void writeData(const void* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
            png_structp _readPngPtr, _writePngPtr;
            png_infop _readInfoPtr, _writeInfoPtr;
            png_error_ptr _errorPtr;
            std::fstream* _stream;
            bool _was_palette;

            //Init libpng structures for reading.
            void initRead();

            //Init libpng structures for writing.
            void initWrite();

            //function used to read data from png file
            static void userReadData(png_structp pngPtr, png_bytep data, png_size_t length)
            {
                png_voidp a = png_get_io_ptr(pngPtr);

                //Cast the pointer to std::istream* and read 'length' bytes into 'data'
                ((std::istream*)a)->read((char*)data, length);
            }

            static void userWriteData(png_structp pngPtr, png_bytep data, png_size_t length)
            {
                png_voidp a = png_get_io_ptr(pngPtr);

                //cast the pointer to std::ostream* and writes 'lenght' byte of data to it.
                ((std::ostream*)a)->write((char*)data, length);
            }

            static void userErrorHandler(png_structp pngPtr, png_const_charp msg)
            {
                throw ImageFileException(std::string("Error while processing png data : ")+reinterpret_cast<const char*>(msg), __LINE__, __FILE__);
            }
    };

    inline unsigned int PngImage::readHeight()
    {
        if(!_readPngPtr) {
            initRead();
        }
        return png_get_image_height(_readPngPtr, _readInfoPtr);
    }

    inline unsigned int PngImage::readWidth()
    {
        if(!_readPngPtr) {
            initRead();
        }
        return png_get_image_width(_readPngPtr, _readInfoPtr);
    }

    inline unsigned int PngImage::readNbChannels()
    {
        if(!_readPngPtr) {
            initRead();
        }
        return (_was_palette) ? 3 : png_get_channels(_readPngPtr, _readInfoPtr);
    }

    inline unsigned int PngImage::readDepth()
    {
        if(!_readPngPtr) {
            initRead();
        }
        return png_get_bit_depth(_readPngPtr, _readInfoPtr);
    }
}

#endif // PNGIMAGE_H
