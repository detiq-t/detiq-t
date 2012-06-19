/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#include "ImageFile.h"

// ImageIn uses the EasyBMP library (http://easybmp.sourceforge.net/), the files from this library are directly included in the project
#include "EasyBMP.h"

namespace imagein
{
	//! ImageFile subclass for BMP files. See ImageFile for details.
    class BmpImage : public ImageFile
    {
        public:
            BmpImage(std::string filename);
			~BmpImage() {delete workImg;}

            inline unsigned int readHeight();
            inline unsigned int readWidth();
            inline unsigned int readNbChannels();
            inline unsigned int readDepth();
            void* readData();

            void writeData(const void* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth);

        private:
            BMP* workImg; // The EasyBMP library object that will be used to read and write in a BMP file
    };
	
	inline unsigned int BmpImage::readHeight()
	{
		return workImg->TellHeight();
	}

	inline unsigned int BmpImage::readWidth()
	{
		return workImg->TellWidth();
	}

	inline unsigned int BmpImage::readNbChannels()
	{
		/* There are always 3 channels (RGB), whatever the depth is,
		   except when the depth is 32, then there is a fourth channel (Alpha) */
		if(readDepth()==32) return 4;
		else return 3;
	}

	inline unsigned int BmpImage::readDepth()
	{
		/* Since a channel is always represented with 8 bits in ImageIn and there are 
		  at least 3 channels (RGB), the minimum depth will be 24 bits. When there is
		  a fourth channel (Alpha), the depth will be 32 bits */
		if(workImg->TellBitDepth() == 32) return 32;
		else return 24;
	}
}

#endif // BMPIMAGE_H
