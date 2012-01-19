#ifndef IMAGEFILEFACTORY_H
#define IMAGEFILEFACTORY_H

#include <string>

#include "ImageFile.h"


namespace imagein
{
    class ImageFileFactory
    {
        public:
            unsigned int getImageDepth(std::string filename);
            virtual ImageFile* getImageFile(std::string filename);
    };
}

#endif // IMAGEFILEFACTORY_H
