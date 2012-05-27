#ifndef COMPONENTLABELINGTESTER_H
#define COMPONENTLABELINGTESTER_H

#include "Tester.h"
#include "ComponentLabelingTest.h"

using namespace imagein;
using namespace imagein::MorphoMat;
using namespace imagein::algorithm;


class ComponentLabelingTester : public Tester {
  public:
    typedef depth_default_t D;
    ComponentLabelingTester()  : Tester("Component labeling") {       
    }

    void init() {

        ComponentLabeling_t<D>::Connectivity con4 = ComponentLabeling_t<D>::CONNECT_4;
        ComponentLabeling_t<D>::Connectivity con8 = ComponentLabeling_t<D>::CONNECT_8;
        
        addTest(new ComponentLabelingTest<D>("Rice (w/ open-close)", "res/rice_openclose_c9.png", 25, 689, con8, true));
        addTest(new ComponentLabelingTest<D>("Rice & sugar", "res/ricensugar.png", 785, 28.67, con8, true));
        addTest(new ComponentLabelingTest<D>("M (w/ white top-hat)", "res/M_wtophat_d15.png", 3, 187, con8, true));
        addTest(new ComponentLabelingTest<D>("QR Code", "res/qrcode.png", 186, 495.14, con4, false));
    }

    void clean() {
    }
};


#endif //!MORPHOMATTESTER_H
