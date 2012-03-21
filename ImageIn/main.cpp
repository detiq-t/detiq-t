#include <iostream>

#include "GrayscaleImage.h"
#include "Image.h"
#include "Otsu.h"
#include "Converter.h"

using namespace std;
using namespace imagein;

int main(int argc, char* argv[])
{
    GrayscaleImage im("samples/grayscale.jpg");
  
    Otsu o;

    GrayscaleImage* out = o(&im);

    out->save("samples/test_otsu.png"); 

    return 0;
}
