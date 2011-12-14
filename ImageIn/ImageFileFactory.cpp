#include "ImageFileFactory.h"

#include "JpgImage.h"
#include "PngImage.h"
#include "BmpImage.h"

using namespace imagein;

unsigned int ImageFileFactory::getImageDepth(std::string filename)
{
    return 0;
}

ImageFile* ImageFileFactory::getImageFile(std::string filename)
{
    return NULL;
}
