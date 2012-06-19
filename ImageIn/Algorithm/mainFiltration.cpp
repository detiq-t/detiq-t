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

#include <list>

#include "../Image.h"
#include "Filtering.h"

using namespace std;
using namespace imagein;
using namespace imagein::algorithm;

int main(int argc, char** argv)
{
	Image img(argv[1]);

	//Filtering filtering = Filtering::prewitt(false, 5);
	//Filtering filtering = Filtering::gaussianBlur(2.0);
	
	Filtering filtering = Filtering::sobel();
	filtering.setNormalization(Filtering::absoluteNormalization);
	//filtering.setPolitic(Filtering::sphericalPolicy);
	filtering(&img)->save("../samples/resultFiltering.png");
	
	return 0;
}
