#include "BmpImage.h"

using namespace imagein;

BmpImage::BmpImage(std::string filename)
 : ImageFile(filename)
{
	/* Setting off the EasyBMP library warnings that are useless for the user of the ImageIn library
	  (replace with SetEasyBMPwarningsOn() in case you want them to appear */
	SetEasyBMPwarningsOff();
	// We create a new BMP object (from EasyBMP library)
	workImg = new BMP();
	/* We try to read from the file at the given adress (filename),
	   if the file exists, its content is loaded, if not we try to create
	   a new file, if it fails an exception is sent */
    if(!workImg->ReadFromFile(_filename.c_str())) {
		if(!workImg->WriteToFile(_filename.c_str())) {
			std::string msg = "The file ";
			msg += _filename;
			msg += " could not be opened or created.";
			throw ImageFileException(msg, __LINE__, __FILE__);
		}
    }
}

void* BmpImage::readData()
{
	// We create a new BMP object (from EasyBMP library)
	if(workImg != NULL) delete workImg;
	workImg = new BMP();
	/* We try to read from the file at the given adress (filename),
	   if the file exists, its content is loaded, otherwise an exception is sent */
    if(!workImg->ReadFromFile(_filename.c_str())) {
		std::string msg = "The file ";
        msg += _filename;
        msg += " could not be opened.";
        throw ImageFileException(msg, __LINE__, __FILE__);
    }
	// We get the image's parameters and create a char matrix with them
	unsigned int w=readWidth(), h=readHeight(), c=readNbChannels();
	uint8_t* data = new uint8_t[w * h * c];
	// We run through the BMP object's matrix of pixels and load each channel into our char matrix
	unsigned int i, j;
	RGBApixel px;
	for(i=0;i<w;i++) {
		for(j=0;j<h;j++) {
			// Getting the current pixel
			px = workImg->GetPixel(i,j);
			// Every pixel is in a RGBA form, we will always get the RGB components, and the Alpha component when necessary
			data[c*(i+j*w)] = px.Red;
			data[c*(i+j*w)+1] = px.Green;
			data[c*(i+j*w)+2] = px.Blue;
			if(c==4) data[c*(i+j*w)+3] = px.Alpha; // In case there are 4 channels, we get the Alpha channel too
		}
	}
	return data;
}

void BmpImage::writeData(const void* const data_, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{
	const uint8_t* const data = reinterpret_cast<const uint8_t* const>(data_);
	
	// We create a new BMP object (from EasyBMP library)
	if(workImg != NULL) delete workImg;
	workImg = new BMP();
	// We initiate the BMP object size
	workImg->SetSize(width,height);
	// We run through our char matrix and load each channel into the BMP object's matrix of pixels
	unsigned int i, j;
	RGBApixel* px;
	for(i=0;i<width;i++) {
		for(j=0;j<height;j++) {
			// Getting the current pixel
			px=(*workImg)(i,j);
			// Every pixel is in a RGBA form, we will always load the RGB components, and the Alpha component when necessary
			px->Red = data[nChannels*(i+j*width)];
			px->Green = data[nChannels*(i+j*width)+1];
			px->Blue = data[nChannels*(i+j*width)+2];
			if(nChannels == 4) px->Alpha = data[nChannels*(i+j*width)+3]; // In case there are 4 channels, we load the Alpha channel too
			//TODO handling of a depth other than char
		}
	}
    /* We try to write to the file at the given adress (filename),
	   if the file doesn't exist, it is created, otherwise it is overwritten
	   if the writing fails an exception is sent */
    if(!workImg->WriteToFile(_filename.c_str())) {
		std::string msg = "The file ";
        msg += _filename;
        msg += " could not be written.";
        throw ImageFileException(msg, __LINE__, __FILE__);
    }
}