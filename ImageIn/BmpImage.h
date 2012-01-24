#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "ImageFile.h"

#include "EasyBMP.h"

namespace imagein
{
    class BmpImage : public ImageFile
    {
        public:
            BmpImage(std::string filename);

            inline unsigned int readHeight();
            inline unsigned int readWidth();
            inline unsigned int readNbChannels();
            inline unsigned int readDepth();
            char* readData();

            void writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
            BMP workImg;
    };
	
	inline unsigned int BmpImage::readHeight()
	{
		return workImg.TellHeight();
	}

	inline unsigned int BmpImage::readWidth()
	{
		return workImg.TellWidth();
	}

	inline unsigned int BmpImage::readNbChannels()
	{
		if(readDepth()==32) return 4;
		else return 3;
	}

	inline unsigned int BmpImage::readDepth()
	{
		return workImg.TellBitDepth();
	}
}

#endif // BMPIMAGE_H
