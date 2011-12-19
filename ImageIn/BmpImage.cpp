#include "BmpImage.h"

using namespace imagein;

BmpImage::BmpImage(std::string filename)
 : ImageFile(filename)
{
    if(!workImg.Load(_filename.c_str())) {
        std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw ImageFileException(msg, __LINE__, __FILE__);
    }
}

unsigned int BmpImage::readHeight()
{
    return workImg.GetHeight();
}

unsigned int BmpImage::readWidth()
{
    return workImg.GetWidth();
}

unsigned int BmpImage::readNbChannels()
{
    //TODO
    return 0;
}

unsigned int BmpImage::readDepth()
{
    //TODO
    return 0;
}

char* BmpImage::readData()
{
    //TODO
    return NULL;
}

void BmpImage::writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{
    //TODO
}
