
//#include "Dithering.h"

#include "../Converter.h"
#include <cmath>

namespace imagein {
	namespace algorithm {
		
		template <typename D>
		typename Dithering_t<D>::DiffusionMatrix* Dithering_t<D>::floydSteinberg()
		{
			DiffusionMatrix* d = new DiffusionMatrix;
			d->width = 3;
			d->height = 2;
			d->total = 16;
			d->center = 1;
			
			int* tab = new int[6];
			tab[0] = 0;
			tab[1] = -1;
			tab[2] = 7;
			tab[3] = 3;
			tab[4] = 5;
			tab[5] = 1;

			d->tab = tab;

			return d;
		}

		template <typename D>
		Image_t<D>* Dithering_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
		{
			//Exception if it isn't grayscale
			/*if(imgs[0]->getNbChannels() != 1) {*/
				/*throw ImageTypeException(__LINE__, __FILE__);*/
			/*}*/
			
			//We need a copy of the image
			/*GrayscaleImage_t<D>* img = Converter<GrayscaleImage_t<D> >::convert(*imgs[0]);*/
			Image_t<D>* img = Converter<Image_t<D> >::convert(*imgs[0]);

			//only floydSteinberg at the moment
			DiffusionMatrix* d = floydSteinberg();

      for(unsigned int nChannel = 0; nChannel < img->getNbChannels(); ++nChannel) {
        //main loop
        for(unsigned int j = 0 ; j < img->getHeight() ; ++j) {
          for(unsigned int i = 0 ; i < img->getWidth() ; ++i) {

            //compute the new value for this pixel
            D pixel = img->getPixel(i, j, nChannel); 
            D value = (pixel <= _threshold) ? 0 : std::numeric_limits<D>::max();
            img->setPixel(i, j, nChannel, value);


            //error propagation
            intmax_t error = pixel-value;
            //std::cout << "pixel (" << i << "," << j << ") - " << (int)pixel << "->" << (int)value << " (error : "<<(int)error<<")"<< std::endl;
            for(unsigned int l = 0 ; l < d->height ; ++l) {
              for(unsigned int k = 0 ; k < d->width ; ++k) {
                
                try {
                  //coef from diffusion matrix
                  intmax_t coef = d->tab[l*(d->width)+k];
                  if(coef > 0) {
                    D oldValue = img->getPixel(i+k-(d->center), j+l, nChannel);
                    intmax_t propError = static_cast<intmax_t>(round(static_cast<double>(coef) * static_cast<double>(error) / static_cast<double>(d->total)));
                    intmax_t newValue = static_cast<intmax_t>(oldValue) + propError;
                    if (newValue > std::numeric_limits<D>::max()) newValue = std::numeric_limits<D>::max();
                    if (newValue < 0) newValue = 0;

                    img->setPixel(i+k-(d->center), j+l, nChannel, newValue);
                    //std::cout << "propagated error to pixel ("<<i+k-(d->center)<<","<<j+l<<") : "<<(int)propError<<". New value : " << newValue << std::endl;
                  }
                }
                catch(const std::out_of_range& e) {}; //if we're out of range, do nothing
              }
            }
            //int rien;
            //std::cin >> rien;
          }
        }
      }

			return img;
		}

	}
}
