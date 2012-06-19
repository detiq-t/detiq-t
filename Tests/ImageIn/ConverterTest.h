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

#ifndef CONVERTERTEST_H
#define CONVERTERTEST_H

#include <string>
#include <sstream>

#include <Image.h>
#include <AlgorithmException.h>
#include <Converter.h>
#include "Test.h"
#include "ImageDiff.h"

template<class T, class F>
class ConverterTest : public Test {

  public:

    ConverterTest(std::string name, F* refImg)
        : Test(name), _refImg(refImg) {}

    virtual bool init() {
        return true;
    }

    virtual bool test() {
        
        T* tmpImg = imagein::Converter<T>::convert(*_refImg);
        F* resImg = imagein::Converter<F>::convert(*tmpImg);

        bool equals = (*_refImg==*resImg);
        delete tmpImg;
        delete resImg;
        return equals;    
    }

    virtual bool cleanup() {
        return true;
    }

    virtual std::string info() {
        return "";
    }

  protected:
    F* _refImg;

    
};

#endif //!COPYTEST_H
