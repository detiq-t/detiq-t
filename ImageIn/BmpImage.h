#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "ImageFile.h"

#include <string>

#include <bitmap.h>
// Cf. http://www.kalytta.com/bitmap.h
// Warning : I had to change the "#include <string>" into "#include <cstring>" for the memset and memcpy methodes

namespace imagein
{
    class BmpImage : public ImageFile
    {
        public:
            BmpImage(std::string filename);

            unsigned int readHeight();
            unsigned int readWidth();
            unsigned int readNbChannels();
            unsigned int readDepth();
            char* readData();

            void writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
            CBitmap workImg;
    };
}

#endif // BMPIMAGE_H
