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
