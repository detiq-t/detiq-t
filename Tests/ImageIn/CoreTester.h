#ifndef CORETESTER_H
#define CORETESTER_H

#include "Tester.h"
#include "CopyTest.h"
#include "CropTest.h"
#include "HistogramTest.h"
#include "ProjHistTest.h"

using namespace imagein;

template <typename D>
class CoreTester : public Tester {
  public:
    CoreTester(Image_t<D>* refImg)  : Tester("ImageIn Core"), _refImg(refImg) {       
        
    }

    void init() {
        addTest(new CopyTest<D>(_refImg));
        addTest(new CropTest());
        addTest(new HistogramTest());
        addTest(new ProjHistTest());
    }

    void clean() {
    }

  protected:
    Image_t<D>* _refImg;
};


#endif //!MORPHOMATTESTER_H
