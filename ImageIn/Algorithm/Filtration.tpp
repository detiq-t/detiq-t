//#include "Filtration.h"

namespace imagein
{
	namespace algorithm
	{
		template<typename D>
		Image_t<D>* Filtration_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
		{
			const Image_t<D>* img = dynamic_cast<const Image_t<D>*>(imgs.at(0));
			
			if(img == NULL) {
				throw ImageTypeException(__LINE__, __FILE__);
			}

			int halfHeightFilter = _filter.height() / 2;
			int halfWidthFilter = _filter.width() / 2;
			
			int posFactor = 0; 
			int negFactor = 0;
			Filter::iterator iter;
			for(iter = _filter.begin; iter != _filter.end(); iter++)
			{
				if((*iter) < 0)
					negFactor += (*iter);
				else
					posFactor += (*iter);
			}
			
			int factor;
			if(posFactor >= -negFactor)
				factor = posFactor;
			else
				factor = -negFactor;
			
			int width = img->getWidth();
			int height = img->getHeight();
			int nChannels = img->getNbChannel();
			
			Image_t<D>* result = new Image_t(unsigned int width, unsigned int height, unsigned int nChannels);
			
			for(int x = 0; x < width; x++)
			{
				for(int y = 0; y < height; y++)
				{
					for(int channel = 0; channel < nChannels; channel++)
					{
						D newPixel = 0;
						for(int i = 0; i < _filter.width(); i++)
						{
							for(int j = 0; j < _filter.height(); j++)
							{
								try
								{
									newPixel += _filter[i][j] * img->getPixel(x + i - halfWidthFilter, y + j - halfHeightFilter, channel);
								}
								catch(out_of_range){}
							}
						}
						if(factor != 0)
						{
							newPixel = newPixel / factor;
							if(newPixel < 0)
								newPixel = 0;
						}
						result->setPixel(x, y, channel, newPixel);
					}
				}
			}
		}
		
		Filtration Filtration::uniformBlur(int coef = 1, int nbPixels = 3)
		{
			Filter filter(nbPixels, nbPixels);
			for(int i = 0; i < nbPixels; i++)
			{
				for(int j = 0; j < nbPixels; j++)
				{
					filter[i][j] = coef;
				}
			}
			Filtration f(filter);
			return f;
		}
		
		Filtration Filtration::prewitt(bool vertical, int nbPixels)
		{
			int width, height;
			if(vertical)
			{
				width = 3;
				height = nbPixels;
			}
			else
			{
				width = nbPixels;
				height = 3;
			}				
			Filter filter(width, height);
			
			for(int i = 0; i < width; i++)
			{
				for(int j = 0; j < height; j++)
				{
					if(vertical && i == 0 || !vertical && j == 0)
						filter[i][j] = -coef;
					else if(vertical && i == width - 1 || !vertical && j == height - 1)
						filter[i][j] = coef;
					else
						filter[i][j] = 0;
				}
			}
			
			Filtration f(filter);
			return f;
		}
	}
}
