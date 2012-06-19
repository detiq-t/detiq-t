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

#ifndef COPYTEST_H
#define COPYTEST_H

#include <string>
#include <sstream>

#include <Image.h>
#include "Test.h"

template<typename D>
class CopyTest : public Test {

  public:

    CopyTest(imagein::Image_t<D>* refImg)
        : Test("Copy constructor"), _refImg(refImg) {}

    virtual bool init() {
        return true;
    }

    virtual bool test() {
        
        imagein::Image copy(*_refImg);

        return ( _refImg->size()==copy.size()
              && std::equal(_refImg->begin(), _refImg->end(), copy.begin()) //Matrices are equals
              && _refImg->getWidth() == copy.getWidth() //Class attributes are equals
              && _refImg->getHeight() == copy.getHeight()
              && _refImg->getNbChannels() == copy.getNbChannels()
        );
    }

    virtual bool cleanup() {
        return true;
    }

    virtual std::string info() {
        return "";
    }

  protected:
    imagein::Image_t<D>* _refImg;

    
};

#endif //!COPYTEST_H
