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

            ~PngImage() { delete _source; /* /!\ handle the deletion of _pngPtr and _infoPtr */ }

            unsigned int readHeight();
            unsigned int readWidth();
            unsigned int readNbChannels();
            unsigned int readDepth();
            char* readData();

            void writeData(char* data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:

            //function used to read data from png file
            static void userReadData(png_structp pngPtr, png_bytep data, png_size_t length)
            {
                png_voidp a = png_get_io_ptr(pngPtr);

                //Cast the pointer to std::istream* and read 'length' bytes into 'data'
                ((std::istream*)a)->read((char*)data, length);
            }

            png_structp _pngPtr;
            png_infop _infoPtr;
            std::istream* _source;
            bool _was_palette;


    };
}

#endif // PNGIMAGE_H
