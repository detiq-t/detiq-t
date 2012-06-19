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

#ifndef IOTEST_H
#define IOTEST_H

#include <string>
#include <sstream>

#include <Image.h>
#include "Test.h"
#include "ImageDiff.h"

template<typename D>
class IOTest : public Test {

  public:

    IOTest(std::string name, imagein::Image_t<D>* refImg, std::string filename, const ImageDiff<D>& maxDiff)
        : Test(name), _refImg(refImg), _filename(filename), _maxDiff(maxDiff), _diff(NULL), _testImg(NULL) {}

    virtual bool init() {
        return true;
    }

    virtual bool test() {
        
        _refImg->save(_filename);
        _testImg = new imagein::Image_t<D>(_filename);
        
        if(_refImg->getWidth() != _testImg->getWidth()) { return false; }
        if(_refImg->getHeight() != _testImg->getHeight()) { return false; }
        if(_refImg->getNbChannels() != _testImg->getNbChannels()) { return false; }

        _diff = new ImageDiff<D>(*_refImg, *_testImg);
        return *_diff <= _maxDiff;
    }

    virtual bool cleanup() {
        delete _testImg;
        return true;
    }

    virtual std::string info() {
        if(_testImg!=NULL) {
            std::ostringstream oss;
            if(_refImg->size()!=_testImg->size()) { 
                oss << "s1=" << (uintmax_t)_refImg->size() << "," << "s2=" << (uintmax_t)_testImg->size();
            }
            if(_refImg->getWidth() != _testImg->getWidth()) {
                oss << "w1=" << _refImg->getWidth() << "," << "w2=" << _refImg->getWidth();
            }
            if(_refImg->getHeight() != _testImg->getHeight()) {
                oss << "h1=" << _refImg->getHeight() << "," << "h2=" << _refImg->getHeight();
            }
            if(_refImg->getNbChannels() != _testImg->getNbChannels()) {
                oss << "c1=" << _refImg->getNbChannels() << "," << "c2=" << _refImg->getNbChannels();
            }
            oss << _diff->toString();
            return oss.str();
        }
        return "";
    }

  protected:
    imagein::Image_t<D>* _refImg;
    std::string _filename;
    ImageDiff<D> _maxDiff;
    ImageDiff<D>* _diff;
    imagein::Image_t<D>* _testImg;

    
};

#endif //!IOTEST_H
