#include <iostream>

#include <list>

#include "GrayscaleImage.h"
#include "Image.h"
#include "Converter.h"
#include "Algorithm/ComponentLabeling.h"
#include "Algorithm/Otsu.h"
#include "Algorithm/Binarization.h"

using namespace std;
using namespace imagein;
using namespace imagein::algorithm;

void printlist(list<int>& l)
{
	for(list<int>::const_iterator it = l.begin() ; it != l.end() ; ++it) {
		cout << *it << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	GrayscaleImage img("samples/binaire.png");
	
	// for(GrayscaleImage::iterator it = img.begin() ; it != img.end() ; ++it) {
		// if(*it != 0 && *it != 255) {
			// cout << "boom" << endl;
		// }
	// }
	
	Binarization b(5);
	
	b(&img);
	
    ComponentLabeling cl(ComponentLabeling::CONNECT_4, false, false);

	cl(Converter<GrayscaleImage>::convert(img))->save("samples/resultcl.png");
	
	cout << cl.getNbComponents() << endl;
	cout << cl.getAverageComponentSize() << endl;
	
	// list<int>* l1 = new list<int>();
	// list<int>* l2 = new list<int>();
	
	// for(int i = 0 ; i < 11 ; ++i) {
		// if(i <= 5) l1->push_back(i);
		// else l2->push_back(i);
	// }
	
	// printlist(*l1);
	// printlist(*l2);
	
	// l1->splice(l1->end(), *l2);
	
	// printlist(*l1);
	// printlist(*l2);
	
	// l1->splice(l1->end(), *l2);
	
	// printlist(*l1);
	// printlist(*l2);
	
    return 0;
}
