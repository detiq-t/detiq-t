#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "ImageFile.h"

#include <string>

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

            void writeData(char* data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
    };
}

#endif // BMPIMAGE_H
