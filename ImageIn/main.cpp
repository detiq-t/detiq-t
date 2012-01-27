#include <iostream>

#include "Image.h"
#include "RgbImage.h"
#include "GrayscaleImage.h"

using namespace std;

int main(int argc, char* argv[])
{
    /*unsigned char* data = new unsigned char[100*100];

    for(unsigned int j = 0 ; j < 100 ; ++j) {
        for(unsigned int i = 0 ; i < 100 ; ++i) {
            data[j*100+i] = i;
        }
    }*/

    try {
        Image test("samples/lena.jpg");

        Image* out = test.crop(Rectangle(100,100,100,100));

        cout << "cp1" << endl;

        out->save("samples/test.jpg");

        cout << "cp2" << endl;
    }
    catch(std::exception& e) {
        cout << e.what() << endl;
    }



    return 0;
}
