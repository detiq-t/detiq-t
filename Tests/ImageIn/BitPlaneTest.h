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

#ifndef BITPLANETEST_H
#define BITPLANETEST_H

#include <string>
#include <sstream>

#include <Image.h>
#include <Algorithm/BitPlane.h>

#include "Test.h"

template<typename D>
class BitPlaneTest : public Test {

  public:

    BitPlaneTest(imagein::Image_t<D>* refImg)
        : Test("BitPlane"), _refImg(refImg), _mask(0), _fail(false) {}

    virtual bool init() {
        return true;
    }

    virtual bool test() {
        
        
        for(D _mask = std::numeric_limits<D>::min(); _mask < std::numeric_limits<D>::max(); ++_mask) {
            imagein::algorithm::BitPlane<Image_t<D> > bitPlane(_mask);
            imagein::Image_t<D>* img = bitPlane(_refImg);
            for(typename imagein::Image_t<D>::iterator it = img->begin(); it < img->end(); ++it) {
                if( (*it & ~_mask) != 0) return _fail = false;
            }
        }
        return true;
    }

    virtual bool cleanup() {
        return true;
    }

    virtual std::string info() {
        if(!_fail) return "";
        std::ostringstream oss;
        oss << "fail on mask " << static_cast<uintmax_t>(_mask);
        return oss.str();
    }

  protected:
    imagein::Image_t<D>* _refImg;
    D _mask;
    bool _fail;

    
};

#endif //!BITPLANETEST_H
