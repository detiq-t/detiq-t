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
  vector<const Image*> d;
  d.push_back(&img);

	Filtration filtration = Filtration::uniformBlur(1, 5);

	std::cout << "-> this : " << &filtration << " ; height : " << filtration._filter.height() << " ; width : " << filtration._filter.width() << std::endl;
	std::cout << "-> this : " << &filtration << " ; height : " << filtration._filter.height() << " ; width : " << filtration._filter.width() << std::endl;
	
  filtration(&img)->save("../samples/resultfiltration.png");
	
	std::cout << "--> height : " << filtration._filter.height() << " ; width : " << filtration._filter.width() << std::endl;

	return 0;
}
