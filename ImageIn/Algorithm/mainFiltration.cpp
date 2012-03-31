#include <iostream>

#include <list>

#include "../Image.h"
#include "Filtration.h"

using namespace std;
using namespace imagein;
using namespace imagein::algorithm;

int main(int argc, char** argv)
{
	Image img("../samples/test.png");

	Filtration filtration = Filtration::uniformBlur();
	
	std::cout << "-> this : " << &filtration << " ; height : " << filtration._filter.height() << " ; width : " << filtration._filter.width() << std::endl;
	
	filtration(&img)->save("../samples/resultfiltration.png");
	
	std::cout << "--> height : " << filtration._filter.height() << " ; width : " << filtration._filter.width() << std::endl;

	return 0;
}
