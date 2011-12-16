#include "BmpImage.h"

using namespace imagein;

BmpImage::BmpImage(std::string filename) : ImageFile(filename)
{
    //TODO
}

unsigned int BmpImage::readWidth()
{
	return 0;
}

unsigned int BmpImage::readNbChannels()
{
	return 0;
}

unsigned int BmpImage::readDepth()
{
	return 0;
}

char* BmpImage::readData()
{
	return NULL;
}

void BmpImage::writeData(char* data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{

}
