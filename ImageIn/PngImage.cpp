#include "PngImage.h"

#include "OpenErrorException.h"

using namespace imagein;
using namespace std;

PngImage::PngImage(string filename)
 : ImageFile(filename)
{
    _pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if(!_pngPtr) {
        throw OpenErrorException("Could not open file "+filename);
    }

    _infoPtr = png_create_info_struct(_pngPtr);

    if(_infoPtr) {
        png_destroy_read_struct(&_pngPtr, (png_infopp)NULL, (png_infopp)NULL);
        throw OpenErrorException("Could not open file "+filename);
    }
}

unsigned int PngImage::readHeight(){
    //TODO
    return 0;
}

unsigned int PngImage::readWidth(){
    //TODO
    return 0;
}

unsigned int PngImage::readNbChannels(){
    //TODO
    return 0;
}

unsigned int PngImage::readDepth(){
    //TODO
    return 0;
}

char* PngImage::readData(){
    //TODO
    return NULL;
}

void PngImage::writeData(char* data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth){
    //TODO
}
