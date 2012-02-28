#include <iostream>

#include "Image.h"
#include "RgbImage.h"
#include "GrayscaleImage.h"
#include "ProjectionHistogram.h"

using namespace std;

int main(int argc, char* argv[])
{
    imagein::Image im("samples/lena.jpg");

    imagein::ProjectionHistogram p(im, static_cast<unsigned char>(50), true);

    return 0;
}
