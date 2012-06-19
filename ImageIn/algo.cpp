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
