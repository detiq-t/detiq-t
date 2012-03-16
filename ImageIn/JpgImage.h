#ifndef JPGIMAGE_H
#define JPGIMAGE_H

#include "ImageFile.h"


namespace imagein
{
	//! ImageFile subclass for JPEG files. See ImageFile for details.
    class JpgImage : public ImageFile
    {
        public:
            JpgImage(std::string filename) : ImageFile(filename) {}

            unsigned int readHeight();
            unsigned int readWidth();
            unsigned int readNbChannels();
            unsigned int readDepth();
            void* readData();

            void writeData(const void* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
    };
}

#endif // JPGIMAGE_H
