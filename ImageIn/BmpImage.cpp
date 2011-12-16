#include "BmpImage.h"
#include <bitmap.h>
// Cf. http://www.kalytta.com/bitmap.h
// Warning : I had to change the "#include <string>" into "#include <cstring>" for the memset and memcpy methodes

using namespace imagein;

unsigned int BmpImage::readHeight(){
    CBitmap workImg = CBitmap();
    if(!workImg.Load(_filename.c_str())) {
        std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw FileNotFoundException(msg.c_str(), __LINE__);
    }
    return workImg.GetHeight();
}

unsigned int BmpImage::readWidth(){
    CBitmap workImg = CBitmap();
    if(!workImg.Load(_filename.c_str())) {
        std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw FileNotFoundException(msg.c_str(), __LINE__);
    }
    return workImg.GetWidth();
}

unsigned int BmpImage::readNbChannels(){
    CBitmap workImg = CBitmap();
    if(!workImg.Load(_filename.c_str())) {
        std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw FileNotFoundException(msg.c_str(), __LINE__);
    }
    //TODO
    return 0;
}

unsigned int BmpImage::readDepth(){
    CBitmap workImg = CBitmap();
    if(!workImg.Load(_filename.c_str())) {
        std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw FileNotFoundException(msg.c_str(), __LINE__);
    }
    //TODO
    return 0;
}

char* BmpImage::readData(){
    CBitmap workImg = CBitmap();
    if(!workImg.Load(_filename.c_str())) {
        std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw FileNotFoundException(msg.c_str(), __LINE__);
    }
    //TODO
    return NULL;
}

void BmpImage::writeData(char* data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth){
    //TODO
}
