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

#ifndef PROJHISTTEST_H
#define PROJHISTTEST_H

#include <string>
#include <sstream>

#include <ProjectionHistogram.h>
#include <Image.h>
#include "Test.h"

class ProjHistTest : public Test {

  public:
    typedef unsigned char D;

    ProjHistTest()
        : Test("Projection histogram"), _refImg(NULL), _hfail(true), _vfail(false), _stop(0), _valueF(0), _valueE(0) {}

    virtual bool init() {
		int width = 320;
		int height = 240;
		int nbChannels = 3;
		unsigned char* dataProj = new unsigned char[width * height * nbChannels];
		for(int i = 0 ; i < width ; ++i) {
			for(int j = 0; j < height ; ++j) {
				if(j>i) {
					dataProj[j*width*nbChannels + i*nbChannels] = 0;
					dataProj[j*width*nbChannels + i*nbChannels +1] = 0;
					dataProj[j*width*nbChannels + i*nbChannels +2] = 0;
				}
				else {
					dataProj[j*width*nbChannels + i*nbChannels] = 255;
					dataProj[j*width*nbChannels + i*nbChannels +1] = 255;
					dataProj[j*width*nbChannels + i*nbChannels +2] = 255;
				}
			}
		}
		_refImg = new imagein::Image_t<D>(width, height, nbChannels, dataProj);
        return true;
    }

    virtual bool test() {
	    _refImg->save("projhist.png");	
        // testing horizontal histogram
		imagein::ProjectionHistogram_t<uint8_t> ph(*_refImg,0,true);
		for(unsigned int i = 0; i < ph.getWidth() ; ++i) {
            _valueF = ph[i];
            _valueE = i;
			if(_valueE != _valueF) {
                return false;
            }
            ++_stop;
		}
        
        _hfail = false;
        _vfail = true;
        _stop = 0;	
        // testing vertical histogram
		imagein::ProjectionHistogram_t<uint8_t> pv(*_refImg,0,false);
		for(unsigned int i = 0; i < pv.getWidth() ; ++i) {
            _valueE = std::max((signed)_refImg->getHeight()-(signed)i-1, 0);
            _valueF = pv[i];
			if(_valueE != _valueF) {
                return false;
            }
            ++_stop;
		}

        _vfail = false;

        return true;
    }

    virtual bool cleanup() {
        delete _refImg;
        return true;
    }

    virtual std::string info() {
        std::ostringstream oss;
        if(_hfail) {
            oss << "hfail on " << _stop << " expected " << (int)_valueE << " got " << (int)_valueF;
        }
        else if(_vfail){
            oss << "vfail on " << _stop << " expected " << (int)_valueE << " got " << (int)_valueF;
        }
        return oss.str();
    }

  protected:
    imagein::Image_t<D>* _refImg;
    bool _hfail;
    bool _vfail;
    unsigned int _stop;
    unsigned int _valueF, _valueE;


    
};

#endif //!PROJHISTTEST_H
