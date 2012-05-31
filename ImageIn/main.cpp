#include <list>
#include "Image.h"
#include "Converter.h"
#include "Algorithm/Otsu.h"
#include "Algorithm/Dithering.h"
#include "Algorithm/EdgeColoration.h"
#include "Algorithm/Filtering.h"
#include "Algorithm/RgbToGrayscale.h"
#include "Converter.h"

#include <ctime>

using namespace imagein;
using namespace imagein::algorithm;
using namespace std;

int main(int argc, char** argv)
{
  srand(time(NULL));
  vector<Filter*> fls =  Filter::sobel();
  
  Filtering c1(fls[0]);
  Filtering c2(fls[1]);

  EdgeColoration_t<Image_t<int>, 2> ec;

  Image* i          = new Image("samples/de.jpg");
  RgbToGrayscale algo;
  Image* img        = algo(i);
  Image_t<int>* i1  = c1(Converter<Image>::convertToInt(*img));
  Image_t<int>* i2  = c2(Converter<Image>::convertToInt(*img));
  Image_t<int>* res = ec(i1, i2);

  Converter<Image>::makeDisplayable(*res)->save("test.png");
}

/*
int main(int argc, char** argv)
{
    Image img("samples/test_dithering.png");

    Dithering d;

    d(Converter<GrayscaleImage>::convert(img))->save("samples/result_dithering.png");
}*/
