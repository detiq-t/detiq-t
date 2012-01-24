#include "BmpImage.h"

using namespace imagein;

BmpImage::BmpImage(std::string filename)
 : ImageFile(filename)
{
	std::cout << "Debut creation" << std::endl;//TODO virer
	workImg = BMP();
	std::cout << "Intermediaire creation" << std::endl;//TODO virer
    if(!workImg.ReadFromFile(_filename.c_str())) {
		std::cout << "Erreur lecture creation" << std::endl;//TODO virer
        std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw ImageFileException(msg, __LINE__, __FILE__);
    }
	std::cout << "Fin creation" << std::endl;//TODO virer
}

char* BmpImage::readData()
{
	std::cout << "Debut lecture" << std::endl; //TODO virer
	unsigned int w=readWidth(), h=readHeight(), c=readNbChannels(), d=readDepth()/8;
	if(d==0) d=1;
	char* data = new char[w * h * c * d];
	unsigned int i, j, k;
	RGBApixel px;
	for(i=0;i<w;i++) {
		for(j=0;j<h;j++) {
			px = workImg.GetPixel(i,j);
			for(k=0;k<d;k++) {
				std::cout << "i:" << i << ", j:" << j << ", k:" << k << std::endl; //TODO virer
				data[k+i*c+j*w*c] = (char)px.Red;
				data[k+d+i*c+j*w*c] = (char)px.Green;
				data[k+2*d+i*c+j*w*c] = (char)px.Blue;
				if(c==4) data[k+3*d+i*c+j*w*c] = (char)px.Alpha;
			}
		}
	}
	return data;
}

void BmpImage::writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{
    //TODO
}
