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

#ifndef CONVERTERTESTER_H
#define CONVERTERTESTER_H

#include "Tester.h"
#include "ConverterTest.h"

using namespace imagein;

template <typename D>
class ConverterTester : public Tester {
  public:
    ConverterTester()  : Tester("Image converter") {       
        
    }

    void init() {
        _rgbImg = new RgbImage_t<D>("res/rose.png");
        _grayImg = new GrayscaleImage_t<D>("res/lena_grayscale.png");
        addTest(new ConverterTest<RgbImage_t<D>, GrayscaleImage_t<D> >("GrayscaleImage <-> RgbImage", _grayImg));
        addTest(new ConverterTest<Image_t<D>, RgbImage_t<D> >("RgbImage <-> Image", _rgbImg));
        addTest(new ConverterTest<Image_t<D>, GrayscaleImage_t<D> >("GrayscaleImage <-> Image", _grayImg));
    }

    void clean() {
        delete _rgbImg;
        delete _grayImg;
    }

  protected:
    RgbImage_t<D>* _rgbImg;
    GrayscaleImage_t<D>* _grayImg;
};


#endif //!CONVERTERTESTER_H
