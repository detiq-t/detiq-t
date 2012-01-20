#include <iostream>

#include "Image.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Writing from nothing.

    unsigned char* data = new unsigned char[255*255];

    for(int j = 0 ; j < 255 ; ++j) {
        for(int i = 0 ; i < 255 ; ++i) {
            data[j*255+i] = i;
        }
    }

    Image<unsigned char> out(255, 255, 1, data);
    out.save("samples/test.png");

    return 0;/**/

    /*//Writing from existing image
    Image<unsigned char> in("samples/Basketball.png");
    Image<unsigned char> out = in.clone();
    out.save("samples/test.png");

    return 0;
    /**/

    /*//Printing image info
    Image<unsigned char> in("samples/test.png");
    cout << in.getWidth() << endl;
    cout << in.getHeight() << endl;
    cout << in.getNbChannels() << endl;
    return 0;
    /**/
}
