//#include "Filtration.h"

#include <algorithm>

namespace imagein
{
	namespace algorithm
	{
		template <typename D>
		Image_t<D>* Filtration_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
		{
		  const Image_t<D>* img = dynamic_cast<const Image_t<D>*>(imgs.at(0));
		  
		  if(img == NULL) {
			throw ImageTypeException(__LINE__, __FILE__);
		  }
		  
		  int posFactor = 0;
		  int negFactor = 0;
		  
		  Filter::iterator iter = _filter.begin();
		  for(iter; iter != _filter.end(); ++iter)
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
		  
		  int halfHeightFilter = _filter.height() / 2;
		  int halfWidthFilter = _filter.width() / 2;
		  int width = img->getWidth();
		  int height = img->getHeight();
		  int nChannels = img->getNbChannels();
		  
		  Image_t<D>* result = new Image_t<D>(width, height, nChannels);
		  
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
					catch(std::out_of_range){}
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
		  
		  return result;
		}
		
		template <typename D>
		Filtration_t<D> Filtration_t<D>::uniformBlur(int coef = 1, int nbPixels = 3)
		{
			Filter filter(nbPixels, nbPixels);
			for(int i = 0; i < nbPixels; i++)
			{
				for(int j = 0; j < nbPixels; j++)
				{
					filter[i][j] = coef;
				}
			}
			return Filtration_t<D>(filter);
		}
		
		template <typename D>
		Filtration_t<D> Filtration_t<D>::prewitt(bool vertical, int nbPixels)
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
						filter[i][j] = -1;
					else if(vertical && i == width - 1 || !vertical && j == height - 1)
						filter[i][j] = 1;
					else
						filter[i][j] = 0;
				}
			}
			
			return Filtration_t<D>(filter);
		}

	template <typename D>
    Filtration_t<D> Filtration_t<D>::gaussianBlur(double alpha)
    {
      std::vector<double> gaussCoef;

      for (int i = 0; ; i++)
      {
        double coef = 10000.0 * std::exp(-(std::pow(i, 2.0)) / (2.0 * std::pow(alpha, 2))) / (2 * M_PI * std::pow(alpha, 2));
        if (coef < 1)
          break;
        else
          gaussCoef.push_back(coef);
      }

      std::cout << gaussCoef.size() * 2 - 1 << std::endl;

      Filter f(gaussCoef.size() * 2 - 1, gaussCoef.size() * 2 - 1);
      int center = gaussCoef.size() - 1;

      for(int i = 0; i < gaussCoef.size(); i++)
      {
        for(int j = i; j < gaussCoef.size(); j++)
        {
          if(i == 0) /* values are already in gaussCoef, so no compute needed */
          {
            f[center][center + j] = gaussCoef[j];

            if(j != 0)
            {
              f[center][center - j] = gaussCoef[j];
              f[center - j][center] = gaussCoef[j];
              f[center + j][center] = gaussCoef[j];
            }
          }
          else
          {
            double coef = 10000.0 * std::exp(-(std::pow(i, 2) + std::pow(j, 2)) / (2 * std::pow(alpha, 2))) / (2 * M_PI * std::pow(alpha, 2));

            f[center + i][center + j] = coef;
            f[center + i][center - j] = coef;
            f[center - i][center + j] = coef;
            f[center - i][center - j] = coef;
            f[center + j][center + i] = coef;
            f[center + j][center - i] = coef;
            f[center - j][center + i] = coef;
            f[center - j][center - i] = coef;
          } 
        }
      }
	  return Filtration_t<D>(f);
    }
  }
}
