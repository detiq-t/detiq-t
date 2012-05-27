#ifndef BINARIZATIONTESTER_H
#define BINARIZATIONTESTER_H

#include "Tester.h"
#include "AlgorithmTest.h"
#include <Algorithm/Binarization.h>
#include <Algorithm/Otsu.h>

using namespace imagein;
using namespace imagein::algorithm;


class BinarizationTester : public Tester {
  public:
    typedef depth_default_t D;
    BinarizationTester() : Tester("Binarization") {       
        
    }

    void init() {
        ImageDiff<D> nodiff(0, 0, 0);
        
        _otsu = new Otsu();
        addTest(new AlgorithmTest<D>("Otsu on harewood", _otsu, "res/harewood.png", "res/harewood_BW.png", nodiff));
        addTest(new AlgorithmTest<D>("Otsu on snow", _otsu, "res/snow.jpg", "res/snow_BW.png", nodiff));
        addTest(new AlgorithmTest<D>("Otsu on nutsBolts", _otsu, "res/nutsBolts.jpg", "res/nutsBolts_BW.png", nodiff));
    }

    void clean() {
        delete _otsu;
    }

  private:
    GenericAlgorithm_t<D>* _otsu;
};


#endif //!BINARIZATIONTESTER_H
