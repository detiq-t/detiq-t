#ifndef BINARYIMAGE_H
#define BINARYIMAGE_H

#include "GrayscaleImage.h"

namespace ImageIn
{
    class BinaryImage : public GrayscaleImage<bool>
    {
        public:
            BinaryImage(unsigned int width, unsigned int height, const bool* data) : GrayscaleImage(width, height, data) {};
            BinaryImage(std::string filename);
            virtual ~BinaryImage();
    };
}

#endif // BINARYIMAGE_H
