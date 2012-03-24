#include <iostream>

#include "GrayscaleImage.h"
#include "Image.h"
#include "Algorithm/Otsu.h"
#include "Converter.h"
#include "Algorithm/Binarization.h"

using namespace std;
using namespace imagein;

int main(int argc, char* argv[])
{
    GrayscaleImage refGray("samples/grayscale.jpg");

    Otsu o;

    (o(&refGray))->save("samples/otsu.jpg");

    return 0;
}
