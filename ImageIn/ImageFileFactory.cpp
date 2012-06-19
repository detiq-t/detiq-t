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

#include <algorithm>

#include "ImageFileFactory.h"

#include "JpgImage.h"
#include "PngImage.h"
#include "BmpImage.h"
#include "UnknownFormatException.h"

using namespace imagein;

unsigned int ImageFileFactory::getImageDepth(std::string filename) const
{
    ImageFile* file = this->getImageFile(filename);

    unsigned int depth = file->readDepth();

    delete file;

    return depth;
}

ImageFile* ImageFileFactory::getImageFile(std::string filename) const
{
    ImageFile* imgf = NULL;
    size_t pos = filename.rfind('.');
    if(pos == std::string::npos) {
      throw UnknownFormatException(__LINE__, __FILE__);
    }

    std::string ext = filename.substr(pos);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    if(ext==".bmp") {
        imgf = new BmpImage(filename);
    }
    else if(ext==".jpg" || filename.substr(filename.size()-5,5)==".jpeg") {
        imgf = new JpgImage(filename);
    }
    else if(ext==".png") {
        imgf = new PngImage(filename);
    }
    else {
      throw UnknownFormatException(__LINE__, __FILE__);
    }
    
    return imgf;
}
