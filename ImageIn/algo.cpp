#include <iostream>

#include "Image.h"
#include "RgbImage.h"
#include "Algorithm.h"
#include "AlgorithmCollection.h"
//#include "Algorithm/BitPlane.h"
//#include "Algorithm/Inversion.h"
#include "Algorithm/Identity.h"
#include "Algorithm/Inversion.h"
#include "Algorithm/BitPlane.h"
#include "Algorithm/Average.h"

using namespace std;
using namespace imagein;
using namespace imagein::algorithm;

int main(int argc, char* argv[])
{
    RgbImage *img = new RgbImage("samples/lena.jpg");
    Identity<RgbImage> identity;
    Inversion<RgbImage> inversion;
    BitPlane<RgbImage> bitplane(128);
    Average<RgbImage, 2> average;
    RgbImage* img2 = inversion(img);
    RgbImage* img3 = average(img, img2);
    img3->save("result.jpg");

    return 0;
}
