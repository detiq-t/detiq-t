#include <list>
#include "Image.h"
#include "Algorithm/Otsu.h"
#include "Algorithm/MorphoMat.h"

using namespace imagein;
using namespace imagein::algorithm;
using namespace std;

/*
int main()
{
	for(list<int>::const_iterator it = l.begin() ; it != l.end() ; ++it) {
		cout << *it << " ";
	}
	cout << endl;
}*/
int main(int argc, char** argv)
{}

/*
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
	
	Image* im_binaire = o(&im);
	im_binaire->save("samples/test.jpg");
	delete im_binaire;
}
*/
