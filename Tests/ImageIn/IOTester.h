#ifndef IOTESTER_H
#define IOTESTER_H

#include <limits>

#include "Tester.h"
#include "IOTest.h"
#include <Image.h>

using namespace imagein;

template<typename D>
class IOTester : public Tester {
  public:
    IOTester(Image_t<D>* refImg)  : Tester("I/O File"), _refImg(refImg) {       
    }

    void init() {
        ImageDiff<D> nodiff(0, 0, 0);
        ImageDiff<D> compression(0, std::numeric_limits<D>::max()/16, 1);
        
        addTest(new IOTest<D>("BMP I/O", _refImg, "iotest.bmp", nodiff));
        addTest(new IOTest<D>("JPEG I/O", _refImg, "iotest.jpg", compression));
        addTest(new IOTest<D>("PNG I/O", _refImg, "iotest.png", nodiff));
    }

    void clean() {
    }

  protected:
    Image_t<D>* _refImg;
};


#endif //!IOTESTER_H
