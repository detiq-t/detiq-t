#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include "ImageFile.h"

#include <iostream>
#include <fstream>

#include <png.h>

namespace imagein
{
    class PngImage : public ImageFile
    {
        public:
            PngImage(std::string filename);

            ~PngImage();

            inline unsigned int readHeight();
            inline unsigned int readWidth();
            inline unsigned int readNbChannels();
            inline unsigned int readDepth();

            char* readData();

            void writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
            png_structp _readPngPtr, _writePngPtr;
            png_infop _infoPtr;
            std::fstream* _stream;
            bool _was_palette;

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
    };

    inline unsigned int PngImage::readHeight()
    {
        if(!_readPngPtr) {
            throw ImageFileException("File "+_filename+" is not a valid png file", __LINE__, __FILE__);
        }
        return png_get_image_height(_readPngPtr, _infoPtr);
    }

    inline unsigned int PngImage::readWidth()
    {
        if(!_readPngPtr) {
            throw ImageFileException("File "+_filename+" is not a valid png file", __LINE__, __FILE__);
        }
        return png_get_image_width(_readPngPtr, _infoPtr);
    }

    inline unsigned int PngImage::readNbChannels()
    {
        if(!_readPngPtr) {
            throw ImageFileException("File "+_filename+" is not a valid png file", __LINE__, __FILE__);
        }
        return (_was_palette) ? 3 : png_get_channels(_readPngPtr, _infoPtr);
    }

    inline unsigned int PngImage::readDepth()
    {
        if(!_readPngPtr) {
            throw ImageFileException("File "+_filename+" is not a valid png file", __LINE__, __FILE__);
        }
        return png_get_bit_depth(_readPngPtr, _infoPtr);
    }
}

#endif // PNGIMAGE_H
