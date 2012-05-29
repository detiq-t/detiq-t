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
