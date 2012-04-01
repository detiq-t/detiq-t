#include <iostream>

#include <list>

#include "../Image.h"
#include "Filtration.h"

using namespace std;
using namespace imagein;
using namespace imagein::algorithm;

int main(int argc, char** argv)
{
	Image img(argv[1]);

	//Filtration filtration = Filtration::prewitt(false, 5);
	//Filtration filtration = Filtration::gaussianBlur(2.0);
	
	Filtration filtration = Filtration::uniformBlur(30, 5);
	filtration.setPolitic(Filtration::sphericalPolitic);
	filtration(&img)->save("../samples/resultfiltration.png");

	return 0;
}
