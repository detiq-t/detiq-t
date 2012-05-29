#include <list>
#include "Image.h"
#include "Converter.h"
#include "Algorithm/Otsu.h"
#include "Algorithm/Dithering.h"

using namespace imagein;
using namespace imagein::algorithm;
using namespace std;

int main(int argc, char** argv)
{
    Image img("samples/test_dithering.png");

    Dithering d;

    d(Converter<GrayscaleImage>::convert(img))->save("samples/result_dithering.png");
}
