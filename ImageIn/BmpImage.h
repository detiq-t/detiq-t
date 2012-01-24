#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "ImageFile.h"

#include <string>
#include <cstring>

#include <bitmap.h>
// Cf. http://www.kalytta.com/bitmap.h
// Warning : I had to add "#include <cstring>" for the memset and memcpy methodes

namespace imagein
{
    class BmpImage : public ImageFile
    {
        public:
            BmpImage(std::string filename);

            unsigned int readHeight();
            unsigned int readWidth();
            unsigned int readNbChannels();
            unsigned int readDepth();
            char* readData();

            void writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
            CBitmap workImg;
    };
	
	inline unsigned int BmpImage::readHeight()
	{
		return workImg.GetHeight();
	}

	inline unsigned int BmpImage::readWidth()
	{
		return workImg.GetWidth();
	}

	inline unsigned int BmpImage::readNbChannels()
	{
		if(readDepth()==32) return 4;
		else return 3;
	}

	inline unsigned int BmpImage::readDepth()
	{
		return workImg.GetBitCount();
	}
}

#endif // BMPIMAGE_H
