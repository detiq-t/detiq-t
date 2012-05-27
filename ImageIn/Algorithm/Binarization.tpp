//#include "Binarization.h"

#include <limits>

namespace imagein {
	namespace algorithm {
		template<typename D>
		GrayscaleImage_t<D>* Binarization_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
		{
            /*const GrayscaleImage_t<D>* img = dynamic_cast<const GrayscaleImage_t<D>*>(imgs.at(0));*/

			if(imgs.at(0)->getNbChannels()>1) {
				throw ImageTypeException(__LINE__, __FILE__);
			}
            const GrayscaleImage_t<D>* img = Converter<GrayscaleImage_t<D> >::convert(*imgs.at(0));

			D* data = new D[img->getWidth() * img->getHeight()];
			D* out = data;
			for(typename GrayscaleImage_t<D>::const_iterator it = img->begin() ; it != img->end() ; ++it) {
				if(_threshold2 > _threshold) { //if there's 2 thresholds
					if(_threshold < *it && *it < _threshold2) { 
						*(out++) = (_blackBand) ? std::numeric_limits<D>::max() : 0;
					}
					else {
						*(out++) = (!_blackBand) ? std::numeric_limits<D>::max() : 0;
					}
				}
				else {
					*(out++) = (*it <= _threshold) ? 0 : std::numeric_limits<D>::max();
				}
			
			}

			GrayscaleImage_t<D>* result = new GrayscaleImage_t<D>(img->getWidth(), img->getHeight(), data);
            delete img;
            return result;
		}
	}
}
