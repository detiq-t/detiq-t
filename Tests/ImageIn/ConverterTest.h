#ifndef CONVERTERTEST_H
#define CONVERTERTEST_H

#include <string>
#include <sstream>

#include <Image.h>
#include <AlgorithmException.h>
#include <Converter.h>
#include "Test.h"
#include "ImageDiff.h"

template<class T, class F>
class ConverterTest : public Test {

  public:

    ConverterTest(std::string name, F* refImg)
        : Test(name), _refImg(refImg) {}

    virtual bool init() {
        return true;
    }

    virtual bool test() {
        
        T* tmpImg = imagein::Converter<T>::convert(*_refImg);
        F* resImg = imagein::Converter<F>::convert(*tmpImg);

        bool equals = (*_refImg==*resImg);
        delete tmpImg;
        delete resImg;
        return equals;    
    }

    virtual bool cleanup() {
        return true;
    }

    virtual std::string info() {
        return "";
    }

  protected:
    F* _refImg;

    
};

#endif //!COPYTEST_H
