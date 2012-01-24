#include "BmpImage.h"

using namespace imagein;

BmpImage::BmpImage(std::string filename)
 : ImageFile(filename)
{
	workImg = BMP();
    if(!workImg.ReadFromFile(_filename.c_str())) {
        std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw ImageFileException(msg, __LINE__, __FILE__);
    }
}

char* BmpImage::readData()
{
	unsigned int w=readWidth(), h=readHeight(), c=readNbChannels(), d=readDepth()/8;
	if(d==0) d=1;
	char* data = new char[w * h * c * d];
	unsigned int i, j, k;
	RGBApixel px;
	for(i=0;i<w;i++) {
		for(j=0;j<h;j++) {
			px = BMP.GetPixel(i,j);
			for(k=0;k<d;k++) {
				data[k+i*c+j*w*c] = px.Red
				data[k+d+i*c+j*w*c] = px.Green;
				data[k+2*d+i*c+j*w*c] = px.Blue;
				if(c==4) data[k+3*d+i*c+j*w*c] = px.Alpha;
			}
		}
	}
	return data;
}

void BmpImage::writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{
    //TODO
}
