/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

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
