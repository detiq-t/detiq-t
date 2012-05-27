#ifndef CROPTEST_H
#define CROPTEST_H

#include <string>
#include <sstream>

#include <Rectangle.h>
#include <Image.h>
#include "Test.h"

class CropTest : public Test {

  public:
    typedef unsigned char D;

    CropTest()
        : Test("Image crop"), _refImg(NULL), _cropImg(NULL) {}

    virtual bool init() {
        //crop reference data
        int width = 128;
        int height = 128;
        int nbChannels = 3;
        unsigned char* dataCrop = new unsigned char[width * height * nbChannels];

        for(int j = 0 ; j < height ; ++j) {
            for(int i = 0 ; i < width ; ++i) {

                unsigned char red, green, blue;

                if(     ((j == 27 || j == 100) && i > 3 && i < 42)
                    ||  ((i == 4 || i == 41) && j > 26 && j < 101)
                  ) {

                    red = 1;
                    green = 2;
                    blue = 3;

                }
                else {
                    red = 255;
                    green = 255;
                    blue = 255;
                }

                dataCrop[j*width*nbChannels + i*nbChannels] = red;
                dataCrop[j*width*nbChannels + i*nbChannels + 1] = green;
                dataCrop[j*width*nbChannels + i*nbChannels + 2] = blue;
            }
        }
        _refImg = new imagein::Image_t<D>(width, height, nbChannels, dataCrop);

        //after crop reference data
        int cropWidth = 38;
        int cropHeight = 74;
        unsigned char* dataAfter = new unsigned char[cropWidth * cropHeight * nbChannels];

        for(int j = 0 ; j < cropHeight ; ++j) {
            for(int i = 0 ; i < cropWidth ; ++i) {

                unsigned char red, green, blue;

                if(i == 0 || i == cropWidth-1 || j == 0 || j == cropHeight-1) {
                    red = 1;
                    green = 2;
                    blue = 3;
                }
                else {
                    red = 255;
                    green = 255;
                    blue = 255;
                }
                dataAfter[j*cropWidth*nbChannels + i*nbChannels] = red;
                dataAfter[j*cropWidth*nbChannels + i*nbChannels + 1] = green;
                dataAfter[j*cropWidth*nbChannels + i*nbChannels + 2] = blue;
            }
        }
        _cropImg = new imagein::Image_t<D>(cropWidth, cropHeight, nbChannels, dataAfter);

        return true;
    }

    virtual bool test() {
        imagein::Image_t<D> *refCrop = _refImg->crop(imagein::Rectangle(4, 27, 38, 74));

        bool success =  ( _cropImg->size()==refCrop->size()
              && std::equal(_cropImg->begin(), _cropImg->end(), refCrop->begin()) //Matrices are equals
              && _cropImg->getWidth() == refCrop->getWidth() //Class attributes are equals
              && _cropImg->getHeight() == refCrop->getHeight()
              && _cropImg->getNbChannels() == refCrop->getNbChannels()
        );

        delete refCrop;
        return success;
        
    }

    virtual bool cleanup() {
        delete _refImg;
        delete _cropImg;
        return true;
    }

    virtual std::string info() {
        return "";
    }

  protected:
    imagein::Image_t<D>* _refImg;
    imagein::Image_t<D>* _cropImg;

    
};

#endif //!CROPTEST_H
