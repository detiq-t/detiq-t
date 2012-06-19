/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

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
