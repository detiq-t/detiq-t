#include "ImageFileFactory.h"

#include "JpgImage.h"
#include "PngImage.h"
#include "BmpImage.h"
#include "UnknownFormatException.h"

using namespace imagein;

unsigned int ImageFileFactory::getImageDepth(std::string filename) const
{
    ImageFile* file = this->getImageFile(filename);

    unsigned int depth = file->readDepth();

    delete file;

    return depth;
}

ImageFile* ImageFileFactory::getImageFile(std::string filename) const
{
    ImageFile* imgf = NULL;
    if(filename.substr(filename.size()-4,4)==".bmp") {
        imgf = new BmpImage(filename);
    }
    else if(filename.substr(filename.size()-4,4)==".jpg" || filename.substr(filename.size()-5,5)==".jpeg") {
        imgf = new JpgImage(filename);
    }
    else if(filename.substr(filename.size()-4,4)==".png") {
        imgf = new PngImage(filename);
    }
	else {
		throw UnknownFormatException(__LINE__, __FILE__);
	}
    return imgf;
}
