#ifndef CONVERTERTESTER_H
#define CONVERTERTESTER_H

#include "Tester.h"
#include "ConverterTest.h"

using namespace imagein;

template <typename D>
class ConverterTester : public Tester {
  public:
    ConverterTester()  : Tester("Image converter") {       
        
    }

    void init() {
        _rgbImg = new RgbImage_t<D>("res/rose.png");
        _grayImg = new GrayscaleImage_t<D>("res/lena_grayscale.png");
        addTest(new ConverterTest<RgbImage_t<D>, GrayscaleImage_t<D> >("GrayscaleImage <-> RgbImage", _grayImg));
        addTest(new ConverterTest<Image_t<D>, RgbImage_t<D> >("RgbImage <-> Image", _rgbImg));
        addTest(new ConverterTest<Image_t<D>, GrayscaleImage_t<D> >("GrayscaleImage <-> Image", _grayImg));
    }

    void clean() {
        delete _rgbImg;
        delete _grayImg;
    }

  protected:
    RgbImage_t<D>* _rgbImg;
    GrayscaleImage_t<D>* _grayImg;
};


#endif //!CONVERTERTESTER_H
