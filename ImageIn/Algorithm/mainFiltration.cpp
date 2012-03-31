#include <iostream>

#include <list>

#include "../Image.h"
#include "Filtration.h"

using namespace std;
using namespace imagein;
using namespace imagein::algorithm;

int main(int argc, char** argv)
{
	Image img("../samples/grayscale.jpg");

	Filtration filtration = Filtration::uniformBlur();
	
	filtration(&img)->save("../samples/resultfiltration.png");

	return 0;
}
