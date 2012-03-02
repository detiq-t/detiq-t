#include <iostream>

#include "Image.h"

using namespace std;
using namespace imagein;

int main(int argc, char* argv[])
{
    int width = 768;
    int height = 512;
    int nbChannels = 3;
    unsigned char* dataRgb = new unsigned char[width * height * nbChannels];

    for(int i = 0 ; i < width ; ++i) { 
        short red = max(255 - i, 255-(768-i));
        if(red < 0) red = 0;
        short green = 255 - abs(256-i);
        if(green < 0) green = 0;
        short blue = 255 - abs(512-i);
        if(blue < 0) blue = 0;
            

        double offset = max(max((double)red/255.0, (double)green/255.0), (double)blue/255.0);
        if(offset<1) red /= offset; green /=offset; blue/=offset;            
        
    	for(int j = 0 ; j < height ; ++j) {
	    short r = red, g = green, b = blue;     
            if(j<256) {
            	r = min(r+256-j, 255);
            	g = min(g+256-j, 255);
            	b = min(b+256-j,255);
            }
	    else {
            	
            	r = max(r+256-j, 0);
            	g = max(g+256-j, 0);
            	b = max(b+256-j,0);
		//r = r*((double)(512-j)/(double)height*2.0);
            	//g = g*((double)(512-j)/(double)height*2.0);
            	//b = b*((double)(512-j)/(double)height*2.0);
	    }
	    
            
	    dataRgb[j*width*nbChannels + i*nbChannels] = r;
            dataRgb[j*width*nbChannels + i*nbChannels + 1] = g;
            dataRgb[j*width*nbChannels + i*nbChannels + 2] = b;
        }
    }
    Image ref(width, height, nbChannels, dataRgb);

    Histogram h = ref.getHistogram(1);

    for(Histogram::const_iterator it = h.begin() ; it != h.end() ; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}
