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

//#include "Otsu.h"

#include "../Histogram.h"
#include "../Converter.h"
#include "Binarization.h"
#include <limits>

namespace imagein {
	namespace algorithm {
		template <typename D>
		GrayscaleImage_t<D>* Otsu_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
		{
            /*const GrayscaleImage_t<D>* img = dynamic_cast<const GrayscaleImage_t<D>*>(imgs.at(0));*/
			
            if(imgs.at(0)->getNbChannels()>1) {
				throw ImageTypeException(__LINE__, __FILE__);
			}
            const GrayscaleImage_t<D>* img = Converter<GrayscaleImage_t<D> >::convert(*imgs.at(0));

			_threshold = computeThreshold(img);

            Binarization_t<D> binarization(_threshold);

			/*D* data = new D[img->getWidth() * img->getHeight()];*/
			/*D* out = data;*/
			/*for(typename GrayscaleImage_t<D>::const_iterator it = img->begin() ; it != img->end() ; ++it) {*/
				/**(out++) = (*it < _threshold) ? 0 : std::numeric_limits<D>::max();*/
			/*}*/

			/*return new GrayscaleImage_t<D>(img->getWidth(), img->getHeight(), data);*/
            return binarization(img);
		}

		template<typename D>
		D Otsu_t<D>::computeThreshold(const GrayscaleImage_t<D>* img)
		{
			//Compute histogram of the image probability of each value.
			Histogram hist = img->getHistogram();
			
			unsigned int nPixel = img->getWidth() * img->getHeight(); 

			//Compute intra-class variance for each possible threshold, and chose the minimum
			int weightb = 0;
			int weightw = 0;
			double sumb = 0;
			double sum = 0;
			for(unsigned int i = 0 ; i < 1<<sizeof(D)*8 ; ++i) {
				sum += i*hist[i];
			}

			double maxVariance = 0;
			unsigned int chosenThreshold = 0;
			for(unsigned int thresh = 0 ; thresh < 1<<sizeof(D)*8; ++thresh) {

				weightb += hist[thresh];
				if(weightb == 0) continue;

				weightw = nPixel - weightb;
				if(weightw == 0) break;

				sumb += thresh*hist[thresh];
				
				double meanb = sumb / static_cast<double>(weightb);
				double meanw = (sum - sumb) / static_cast<double>(weightw);

				double variance = static_cast<double>(weightb) * static_cast<double>(weightw) * (meanb - meanw) * (meanb - meanw);

				//if this variance is lower greater than previous maximum, replace previous threshold with this one.
				//Always replace if this is the first threshold tried.
				if (variance > maxVariance) {
					maxVariance = variance;
					chosenThreshold = thresh;
				}
			}

			return chosenThreshold;
		}
	}
}
