#include <algorithm>

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
    size_t pos = filename.rfind('.');
    if(pos == std::string::npos) {
      throw UnknownFormatException(__LINE__, __FILE__);
    }

    std::string ext = filename.substr(pos);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    std::cout << ext << std::endl;
    if(ext==".bmp") {
        imgf = new BmpImage(filename);
    }
    else if(ext==".jpg" || filename.substr(filename.size()-5,5)==".jpeg") {
        imgf = new JpgImage(filename);
    }
    else if(ext==".png") {
        imgf = new PngImage(filename);
    }
    else {
      throw UnknownFormatException(__LINE__, __FILE__);
    }
    
    return imgf;
}
