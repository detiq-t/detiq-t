#ifndef COPYTEST_H
#define COPYTEST_H

#include <string>
#include <sstream>

#include <Image.h>
#include "Test.h"

template<typename D>
class CopyTest : public Test {

  public:

    CopyTest(imagein::Image_t<D>* refImg)
        : Test("Copy constructor"), _refImg(refImg) {}

    virtual bool init() {
        return true;
    }

    virtual bool test() {
        
        imagein::Image copy(*_refImg);

        return ( _refImg->size()==copy.size()
              && std::equal(_refImg->begin(), _refImg->end(), copy.begin()) //Matrices are equals
              && _refImg->getWidth() == copy.getWidth() //Class attributes are equals
              && _refImg->getHeight() == copy.getHeight()
              && _refImg->getNbChannels() == copy.getNbChannels()
        );
    }

    virtual bool cleanup() {
        return true;
    }

    virtual std::string info() {
        return "";
    }

  protected:
    imagein::Image_t<D>* _refImg;

    
};

#endif //!COPYTEST_H
