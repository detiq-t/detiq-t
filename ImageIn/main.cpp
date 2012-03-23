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
    RgbImage refRgb("samples/lena.jpg");
    Image refIm("samples/lena_24.png");

    Image* image = Converter<Image>::convert(refGray);
    RgbImage* rgb = Converter<RgbImage>::convert(refGray);
    GrayscaleImage* gray = Converter<GrayscaleImage>::convert(refGray);

    image->save("samples/conv_gray_im.jpg");
    rgb->save("samples/conv_gray_rgb.jpg");
    gray->save("samples/conv_gray_gray.jpg");

    image = Converter<Image>::convert(refRgb);
    gray = Converter<GrayscaleImage>::convert(refRgb);
    rgb = Converter<RgbImage>::convert(refRgb);

    image->save("samples/conv_rgb_im.jpg");
    rgb->save("samples/conv_rgb_rgb.jpg");
    gray->save("samples/conv_rgb_gray.jpg");

    image = Converter<Image>::convert(refIm);
    gray = Converter<GrayscaleImage>::convert(refIm);
    rgb = Converter<RgbImage>::convert(refIm);

    image->save("samples/conv_im_im.jpg");
    rgb->save("samples/conv_im_rgb.jpg");
    gray->save("samples/conv_im_gray.jpg");

    return 0;
}
