#ifndef IMAGEFILEFACTORY_H
#define IMAGEFILEFACTORY_H

#include <string>

#include "ImageFile.h"


namespace imagein
{
    namespace ImageFileFactory
    {
        unsigned int getImageDepth(std::string filename);
        ImageFile* getImageFile(std::string filename);
    };
}

#endif // IMAGEFILEFACTORY_H
