#ifndef UTILITYTESTER_H
#define UTILITYTESTER_H

#include "Tester.h"
#include "AlgorithmTest.h"
#include "BitPlaneTest.h"
#include <Algorithm/Identity.h>
#include <Algorithm/Inversion.h>
#include <Algorithm/Average.h>
#include <Algorithm/Difference.h>
#include <Algorithm/BitPlane.h>

using namespace imagein;
using namespace algorithm;

class UtilityTester : public Tester {
  public:
    typedef depth_default_t D;
    UtilityTester(Image_t<D>* refImg)  : Tester("Utility algorithms"), _refImg(refImg) {       
    }

    void init() {
        
        ImageDiff<D> nodiff(0, 0, 0);
        
        addTest(new AlgorithmTest<D>("Identity", new Identity<Image_t<D> >(), "res/lena.png", "res/lena.png", nodiff));
        addTest(new AlgorithmTest<D>("Inversion", new Inversion<Image_t<D> >(), "res/lena.png", "res/lena_inverted.png", nodiff));
        addTest(new AlgorithmTest<D, 2>("Difference", new Difference<Image_t<D> >(), "res/lena_white.png", "res/lena_inverted.png", "res/lena.png", nodiff));
        addTest(new AlgorithmTest<D, 2>("Average", new Average<Image_t<D>, 2>(), "res/lena.png", "res/lena_inverted.png", "res/lena_gray127.png", nodiff));
        addTest(new BitPlaneTest<D>(_refImg));
    }

    void clean() {
    }

  private:
    Image_t<D>* _refImg;
};


#endif //!UTILITYTESTER_H
