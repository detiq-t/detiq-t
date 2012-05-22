#include <iostream>

#include <list>

#include "GrayscaleImage.h"
#include "Image.h"
#include "Converter.h"
#include "Algorithm/ComponentLabeling.h"
#include "Algorithm/Otsu.h"
#include "Algorithm/Binarization.h"
#include "Algorithm/MorphoMat.h"

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

int main(int argc, char** argv)
{


	Image_t<depth8_t> img("samples/lena.jpg");
    
    bool elem[] = {
        false, true, false,
        true,  true, true,
        false, true, false
    };

    MorphoMat::StructElem<depth8_t> structElem(GrayscaleImage_t<bool>(3, 3, elem), 1, 1);
    MorphoMat::Gradient<depth8_t> grad(structElem);
    Image *res = grad(&img);
    res->save("morpho.jpg");

    return 0;
}

#ifdef AUTREMAIN
int main(int argc, char* argv[])
{
	GrayscaleImage img("samples/test.png");
	
	// for(GrayscaleImage::iterator it = img.begin() ; it != img.end() ; ++it) {
		// if(*it != 0 && *it != 255) {
			// cout << "boom" << endl;
		// }
	// }
	
	//Binarization b(5);
	
	//b(&img);
	
    //ComponentLabeling cl(ComponentLabeling::CONNECT_4, false, false);

	//cl(Converter<GrayscaleImage>::convert(img))->save("samples/resultcl.png");
	
	//cout << cl.getNbComponents() << endl;
	//cout << cl.getAverageComponentSize() << endl;
	
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
#endif
