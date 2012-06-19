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

namespace imagein {
	namespace algorithm {
		template<typename D>
        Image_t<D>* RgbToGrayscale_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
		{
            const Image_t<D>* img = dynamic_cast<const Image_t<D>*>(imgs.at(0));
            if (img->getNbChannels() >= 3)
			{

                GrayscaleImage_t<D>* img_res = new GrayscaleImage_t<D>(img->getWidth(), img->getHeight());
                for (int j = 0 ; j < img->getHeight() ; ++j)
                {
                    for (int i = 0 ; i < img->getWidth() ; ++i)
                    {
                        img_res->setPixel(i, j, img->getPixel(i, j, 0) * _r
                                                + img->getPixel(i, j, 1) * _g
                                                + img->getPixel(i, j, 2) * _b );
                    }
                }
                return img_res;
            }
            else
                return Converter<GrayscaleImage_t<D> >::convert(*img);
		}
	}
}
