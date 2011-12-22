#ifndef BINARYIMAGE_H
#define BINARYIMAGE_H

#include "GrayscaleImage.h"

namespace imagein
{
    class BinaryImage : public GrayscaleImage<bool>
    {
        public:
            BinaryImage(unsigned int width, unsigned int height, bool* data) : GrayscaleImage<bool>(width, height, data) {};
            BinaryImage(std::string filename);
            virtual ~BinaryImage();
    };
}

#endif // BINARYIMAGE_H
