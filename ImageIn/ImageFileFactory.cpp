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
    ImageFile* imgf = NULL;
    if(filename.substr(filename.size()-4,4)==".bmp") {
        imgf = new BmpImage(filename);
        return imgf;
    }
    else if(filename.substr(filename.size()-4,4)==".jpg" || filename.substr(filename.size()-5,5)==".jpeg") {
        imgf = new JpgImage(filename);
        return imgf;
    }
    if(filename.substr(filename.size()-4,4)==".png") {
        imgf = new PngImage(filename);
        return imgf;
    }
    // TODO : add webp
    else {
        return imgf;
    }
}
