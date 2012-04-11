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
