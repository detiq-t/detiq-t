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

#ifndef COMPONENTLABELINGTEST_H
#define COMPONENTLABELINGTEST_H

#include <string>
#include <sstream>

#include <Image.h>
#include <Converter.h>
#include <Algorithm/ComponentLabeling.h>

#include "Test.h"

template<typename D>
class ComponentLabelingTest : public Test {


    public:
    typedef typename imagein::algorithm::ComponentLabeling_t<D>::Connectivity Connectivity;

    ComponentLabelingTest(std::string name, std::string refImgName, unsigned int nComponent, double averageSize, Connectivity connectivity, bool blackBkg)
        : Test(name), _refImgName(refImgName), _refImg(NULL), _nComponentE(nComponent), _averageSizeE(averageSize), _fail(false), _connectivity(connectivity), _blackBkg(blackBkg) {}

    virtual bool init() {
        imagein::Image_t<D>* tmpImg = new imagein::Image_t<D>(_refImgName);
        _refImg = Converter<GrayscaleImage_t<D> >::convert(*tmpImg);
        delete tmpImg;
        return true;
    }

    virtual bool test() {
       
        imagein::algorithm::ComponentLabeling_t<D> label(_connectivity, _blackBkg, true);
        imagein::Image_t<D>* img = label(_refImg);
        _averageSizeF = label.getAverageComponentSize();
        _nComponentF = label.getNbComponents();

        _fail = ( (_nComponentF!=_nComponentE) || ((_averageSizeF-_averageSizeE)/_averageSizeE)>0.01 );

        return !_fail;
    }

    virtual bool cleanup() {
        delete _refImg;
        return true;
    }

    virtual std::string info() {
        if(!_fail) return "";
        std::ostringstream oss;
        oss << "expected " << _nComponentE << "x" << _averageSizeE << " got " << _nComponentF << "x" << _averageSizeF;
        return oss.str();
    }

  protected:
    std::string _refImgName;
    imagein::GrayscaleImage_t<D>* _refImg;
    unsigned int _nComponentE;
    double _averageSizeE;
    unsigned int _nComponentF;
    double _averageSizeF;
    bool _fail;
    Connectivity _connectivity;
    bool _blackBkg;

    
};

#endif //!BITPLANETEST_H
