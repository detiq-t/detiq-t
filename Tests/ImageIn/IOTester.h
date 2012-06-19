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

#ifndef IOTESTER_H
#define IOTESTER_H

#include <limits>

#include "Tester.h"
#include "IOTest.h"
#include <Image.h>

using namespace imagein;

template<typename D>
class IOTester : public Tester {
  public:
    IOTester(Image_t<D>* refImg)  : Tester("I/O File"), _refImg(refImg) {       
    }

    void init() {
        ImageDiff<D> nodiff(0, 0, 0);
        ImageDiff<D> compression(0, std::numeric_limits<D>::max()/16, 1);
        
        addTest(new IOTest<D>("BMP I/O", _refImg, "iotest.bmp", nodiff));
        addTest(new IOTest<D>("JPEG I/O", _refImg, "iotest.jpg", compression));
        addTest(new IOTest<D>("PNG I/O", _refImg, "iotest.png", nodiff));
    }

    void clean() {
    }

  protected:
    Image_t<D>* _refImg;
};


#endif //!IOTESTER_H
