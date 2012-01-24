#include <iostream>

#include "Image.h"
#include "GrayscaleImage.h"

using namespace std;

int main(int argc, char* argv[])
{
    /*//Writing from nothing.

    unsigned int* data = new unsigned int[1800*900];

    for(unsigned int j = 0 ; j < 900 ; ++j) {
        for(unsigned int i = 0 ; i < 1800 ; ++i) {
            data[j*1800+i] = i;
        }
    }

    Image<unsigned int> out(1800, 900, 1, data);
    out.save("samples/test.jpg");

    return 0;/**/

    //Writing from existing image
    Image<unsigned char> in("samples/lena.bmp");
    Image<unsigned char> out = in.clone();
    out.save("samples/test.png");

    return 0;
    /**/

    /*//Printing image info
    Image<unsigned char> in("samples/lena.bmp");
    cout << in.getWidth() << endl;
    cout << in.getHeight() << endl;
    cout << in.getNbChannels() << endl;
    return 0;
    /**/
}
