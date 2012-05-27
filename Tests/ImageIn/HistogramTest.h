#ifndef HISTOGRAMTEST_H
#define HISTOGRAMTEST_H

#include <string>
#include <sstream>

#include <Histogram.h>
#include <Image.h>
#include "Test.h"

class HistogramTest : public Test {

  public:
    typedef unsigned char D;

    HistogramTest()
        : Test("Histogram"), _refImg(NULL), _fail(true), _stop(0), _valueF(0), _valueE(0) {}

    virtual bool init() {
        //Reference Image
        int width = 768;
        int height = 512;
        int nbChannels = 3;
        unsigned char* dataRgb = new unsigned char[width * height * nbChannels];

        for(int i = 0 ; i < width ; ++i) {
            short red = std::max(255 - i, 255-(768-i));
            if(red < 0) red = 0;
            short green = 255 - std::abs(256-i);
            if(green < 0) green = 0;
            short blue = 255 - std::abs(512-i);
            if(blue < 0) blue = 0;

            double offset = std::max(std::max((double)red/255.0, (double)green/255.0), (double)blue/255.0);
            if(offset<1) red /= offset; green /=offset; blue/=offset;

            for(int j = 0 ; j < height ; ++j) {
            short r = red, g = green, b = blue;
                if(j<256) {
                    r = std::min(r+256-j, 255);
                    g = std::min(g+256-j, 255);
                    b = std::min(b+256-j,255);
                }
                else {

                        r = std::max(r+256-j, 0);
                        g = std::max(g+256-j, 0);
                        b = std::max(b+256-j,0);
                }

                dataRgb[j*width*nbChannels + i*nbChannels] = r;
                dataRgb[j*width*nbChannels + i*nbChannels + 1] = g;
                dataRgb[j*width*nbChannels + i*nbChannels + 2] = b;
            }
        }
		_refImg = new imagein::Image_t<D>(width, height, nbChannels, dataRgb);
        return true;
    }

    virtual bool test() {
        // testing horizontal histogram
		imagein::Histogram hist(*_refImg);
        ++_stop;
		for(unsigned int i = 1; i < hist.getWidth()-1 ; ++i) {
            _valueF = hist[i];
            _valueE = 768;
            if(_valueE != _valueF) {
                return false;
            }
            ++_stop;
		}
        
        _fail = false;
        return true;
    }

    virtual bool cleanup() {
        delete _refImg;
        return true;
    }

    virtual std::string info() {
        std::ostringstream oss;
        if(_fail) {
            oss << "fail on " << _stop << " expected " << _valueE << " got " << _valueF;
        }
        return oss.str();
    }

  protected:
    imagein::Image_t<D>* _refImg;
    bool _fail;
    unsigned int _stop;
    unsigned int _valueF, _valueE;


    
};

#endif //!PROJHISTTEST_H
