#include <iostream>

#include "AlgorithmTest.h"
#include "Tester.h"
#include <Algorithm/MorphoMat.h>

#include "CoreTester.h"
#include "IOTester.h"
#include "ConverterTester.h"
#include "UtilityTester.h"
#include "MorphoMatTester.h"
#include "BinarizationTester.h"
#include "ComponentLabelingTester.h"
#include "FilteringTester.h"

using namespace imagein;
using namespace imagein::MorphoMat;
using namespace imagein::algorithm;
typedef depth_default_t D;

Image_t<D>* generateRefImg();

int main(int argc, char** argv) {
    
    Image_t<D> *refImg = generateRefImg();
    
    unsigned int error = 0;

    error += CoreTester<D>(refImg)();
    error += IOTester<D>(refImg)();
    error += ConverterTester<D>()();
    error += UtilityTester(refImg)();
    error += MorphoMatTester()();
    error += BinarizationTester()();
    error += ComponentLabelingTester()();
    error += FilteringTester()();
    
    delete refImg;

    return error;
}

Image_t<D>* generateRefImg() {
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
    return new Image_t<D>(width, height, nbChannels, dataRgb);
}
