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
