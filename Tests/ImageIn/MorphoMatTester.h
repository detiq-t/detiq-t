#ifndef MORPHOMATTESTER_H
#define MORPHOMATTESTER_H

#include "Tester.h"
#include "AlgorithmTest.h"
#include <Algorithm/MorphoMat.h>

using namespace imagein;
using namespace imagein::MorphoMat;
using namespace imagein::algorithm;


class MorphoMatTester : public Tester {
  public:
    typedef depth_default_t D;
    MorphoMatTester()  : Tester("Mathematical morphology") {       
    }

    void init() {
        
        ImageDiff<D> nodiff(0, 0, 0);
        
        StructElem<depth_default_t> d15("res/diamond15x15.png");
        StructElem<depth_default_t> d3("res/diamond3x3.png");
        
        //addTest(new AlgorithmTest<D>("Erosion d15", new Erosion<D>(d15), "res/rose.png", "res/rose_erosion_diamond15x15.png", nodiff));
        //addTest(new AlgorithmTest<D>("Dilatation d15", new Dilatation<D>(d15), "res/rose.png", "res/rose_dilatation_diamond15x15.png", nodiff));
        //addTest(new AlgorithmTest<D>("Opening d15", new Opening<D>(d15), "res/rose.png", "res/rose_opening_diamond15x15.png", nodiff));
        //addTest(new AlgorithmTest<D>("Closing d15", new Closing<D>(d15), "res/rose.png", "res/rose_closing_diamond15x15.png", nodiff));
        //addTest(new AlgorithmTest<D>("Gradient d3", new Gradient<D>(d3), "res/rose.png", "res/rose_gradient_diamond3x3.png", nodiff));
        //addTest(new AlgorithmTest<D>("White Top Hat d15", new WhiteTopHat<D>(d15), "res/rose.png", "res/rose_wtophat_diamond15x15.png", nodiff));
        //addTest(new AlgorithmTest<D>("Black Top Hat d15", new BlackTopHat<D>(d15), "res/rose.png", "res/rose_btophat_diamond15x15.png", nodiff));
        
        addTest(new AlgorithmTest<D>("Erosion d15 on M", new Erosion<D>(d15), "res/M.png", "res/M_erosion_d15.png", nodiff));
        addTest(new AlgorithmTest<D>("Dilatation d15 on M", new Dilatation<D>(d15), "res/M.png", "res/M_dilatation_d15.png", nodiff));
        addTest(new AlgorithmTest<D>("Opening d15 on M", new Opening<D>(d15), "res/M.png", "res/M_opening_d15.png", nodiff));
        addTest(new AlgorithmTest<D>("Closing d15 on M", new Closing<D>(d15), "res/M.png", "res/M_closing_d15.png", nodiff));
        addTest(new AlgorithmTest<D>("Gradient d3 on M", new Gradient<D>(d3), "res/M.png", "res/M_gradient_d3.png", nodiff));
        addTest(new AlgorithmTest<D>("White Top Hat d15 on M", new WhiteTopHat<D>(d15), "res/M.png", "res/M_wtophat_d15.png", nodiff));
        addTest(new AlgorithmTest<D>("Black Top Hat d15 on M", new BlackTopHat<D>(d15), "res/M.png", "res/M_btophat_d15.png", nodiff));
        addTest(new AlgorithmTest<D>("Gradient d3 on rose", new Gradient<D>(d3), "res/rose.png", "res/rose_gradient_diamond3x3.png", nodiff));
        addTest(new AlgorithmTest<D>("Gradient d3 on lena", new Gradient<D>(d3), "res/lena.png", "res/lena_gradient_d3.png", nodiff));
    }

    void clean() {
    }
};


#endif //!MORPHOMATTESTER_H
