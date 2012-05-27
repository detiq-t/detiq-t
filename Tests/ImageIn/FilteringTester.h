#ifndef FILTERINGTESTER_H
#define FILTERINGTESTER_H

#include "Tester.h"
#include "FilteringTest.h"
#include <Algorithm/Filtering.h>

using namespace imagein;
using namespace imagein::algorithm;


class FilteringTester : public Tester {
  public:
    typedef depth_default_t D;
    FilteringTester() : Tester("Filtering") {       
        
    }

    void init() {
        ImageDiff<D> nodiff(0, 0, 0);
        
        Filtering* gaussian = new Filtering(Filter::gaussian(3));
        addTest(new FilteringTest<D>("Gaussian blur", gaussian, "res/lena.png", "res/lena_gaussian_16.png", nodiff));
    }

    void clean() {
    }
};


#endif //!FILTERINGTESTER_H
