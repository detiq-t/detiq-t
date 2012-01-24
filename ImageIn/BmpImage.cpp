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

char* BmpImage::readData()
{
	unsigned int w=readWidth(), h=readHeight(), c=readNbChannels(), d=d/8;
	if(d==0) d=1;
	char* data = new char[w * h * c * d];
	unsigned int size = w*h*c*d;
	workImg.GetBits(data, size, 5, 6, 5, 0);
	return data;
}

void BmpImage::writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{
    //TODO
}
