#include "BmpImage.h"

using namespace imagein;

BmpImage::BmpImage(std::string filename)
 : ImageFile(filename)
{
	SetEasyBMPwarningsOff();
	workImg = new BMP();
    if(!workImg->ReadFromFile(_filename.c_str())) {
		workImg->WriteToFile(_filename.c_str());
        /*std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw ImageFileException(msg, __LINE__, __FILE__);*/
    }
}

char* BmpImage::readData()
{
	unsigned int w=readWidth(), h=readHeight(), c=readNbChannels();
	char* data = new char[w * h * c];
	unsigned int i, j;
	RGBApixel px;
	for(i=0;i<w;i++) {
		for(j=0;j<h;j++) {
			px = workImg->GetPixel(i,j);
			data[c*(i+j*w)] = (char)px.Red;
			data[c*(i+j*w)+1] = (char)px.Green;
			data[c*(i+j*w)+2] = (char)px.Blue;
			if(c==4) data[c*(i+j*w)+3] = (char)px.Alpha;
		}
	}
	return data;
}

void BmpImage::writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{
	delete workImg;
	workImg = new BMP();
	workImg->SetSize(width,height);
	unsigned int i, j;
	RGBApixel* px;
	for(i=0;i<width;i++) {
		for(j=0;j<height;j++) {
			px=(*workImg)(i,j);
			px->Red = data[nChannels*(i+j*width)];
			px->Green = data[nChannels*(i+j*width)+1];
			px->Blue = data[nChannels*(i+j*width)+2];
			if(nChannels == 4) px->Alpha = data[nChannels*(i+j*width)+3];
			//TODO gérer les profondeurs supérieures au char
		}
	}
    workImg->WriteToFile(_filename.c_str());
}
