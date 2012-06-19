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
