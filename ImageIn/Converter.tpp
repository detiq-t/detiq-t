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

//#include "Converter.h"

namespace imagein {

  template <typename D>
  RgbImage_t<D>* Converter<RgbImage_t<D> >::convert(const GrayscaleImage_t<D>& from) 
  {
      D* data = new D[from.getWidth() * from.getHeight() * 3];
      D* ptr = data;

      for(typename Image_t<D>::const_iterator it = from.begin() ; it != from.end() ; ++it) {
          *(ptr++) = *it;
          *(ptr++) = *it;
          *(ptr++) = *it;
      }

      return new RgbImage_t<D>(from.getWidth(), from.getHeight(), data);
  }

  template <typename D>
  RgbImage_t<D>* Converter<RgbImage_t<D> >::convert(const RgbImage_t<D>& from)
  {
      return new RgbImage_t<D>(from.getWidth(), from.getHeight(), from.begin());
  }

  template <typename D>
  RgbImage_t<D>* Converter<RgbImage_t<D> >::convert(const Image_t<D>& from) 
  {
      D* data = new D[from.getWidth() * from.getHeight() * 3];
      D* ptr = data;

      if (from.getNbChannels() < 3) {
          for(int j = 0 ; j < from.getHeight() ; ++j) {
              for(int i = 0 ; i < from.getWidth() ; ++i) {
                  *(ptr++) = from.getPixel(i, j, 0);
                  *(ptr++) = from.getPixel(i, j, 0);
                  *(ptr++) = from.getPixel(i, j, 0);
              }
          }
      }
      else {
          for(int j = 0 ; j < from.getHeight() ; ++j) {
              for(int i = 0 ; i < from.getWidth() ; ++i) {
                  *(ptr++) = from.getPixel(i, j, 0);
                  *(ptr++) = from.getPixel(i, j, 1);
                  *(ptr++) = from.getPixel(i, j, 2);
              }
          }
      }

      return new RgbImage_t<D>(from.getWidth(), from.getHeight(), data);
  }

  template <typename D>
  GrayscaleImage_t<D>* Converter<GrayscaleImage_t<D> >::convert(const GrayscaleImage_t<D>& from)
  {
      return new GrayscaleImage_t<D>(from.getWidth(), from.getHeight(), from.begin());
  }

  template <typename D>
  GrayscaleImage_t<D>* Converter<GrayscaleImage_t<D> >::convert(const RgbImage_t<D>& from) 
  {
      D* data = new D[from.getWidth() * from.getHeight()];
      D* ptr = data;

      for(int j = 0 ; j < from.getHeight() ; ++j) {
          for(int i = 0 ; i < from.getWidth() ; ++i) {
              *(ptr++) = 
                  ( from.getPixel(i, j, 0) + 
                    from.getPixel(i, j, 1) + 
                    from.getPixel(i, j, 2)
                  ) / 3;
          }
      }

      return new GrayscaleImage_t<D>(from.getWidth(), from.getHeight(), data);
  }

  template <typename D>
  GrayscaleImage_t<D>* Converter<GrayscaleImage_t<D> >::convert(const Image_t<D>& from) 
  {
      D* data = new D[from.getWidth() * from.getHeight()];
      D* ptr = data;

      if (from.getNbChannels() < 3) {
          for(unsigned int j = 0 ; j < from.getHeight() ; ++j) {
              for(unsigned int i = 0 ; i < from.getWidth() ; ++i) {
                  *(ptr++) = from.getPixel(i, j, 0);
              }
          }
      }
      else {
          for(unsigned int j = 0 ; j < from.getHeight() ; ++j) {
              for(unsigned int i = 0 ; i < from.getWidth() ; ++i) {
                  *(ptr++) = 
                      ( from.getPixel(i, j, 0) + 
                        from.getPixel(i, j, 1) + 
                        from.getPixel(i, j, 2)
                      ) / 3;
              }
          }
      }

      return new GrayscaleImage_t<D>(from.getWidth(), from.getHeight(), data);
  }

  template <typename D>
  Image_t<D>* Converter<Image_t<D> >::convert(const GrayscaleImage_t<D>& from)
  {
      return new Image_t<D>(from.getWidth(), from.getHeight(), 1, from.begin());
  }

  template <typename D>
  Image_t<D>* Converter<Image_t<D> >::convert(const RgbImage_t<D>& from)
  {
      return new Image_t<D>(from.getWidth(), from.getHeight(), 3, from.begin());
  }

  template <typename D>
  Image_t<D>* Converter<Image_t<D> >::convert(const Image_t<D>& from)
  {
      return new Image_t<D>(from.getWidth(), from.getHeight(), from.getNbChannels(), from.begin());
  }

  template <typename D>
  Image_t<int>* Converter<Image_t<D> >::convertToInt(const Image_t<D>& from)
  {
    Image_t<int>* image = new Image_t<int>(from.getWidth(), from.getHeight(), from.getNbChannels());
    for(unsigned int i = 0; i < from.getWidth(); i++)
    {
      for(unsigned int j = 0; j < from.getHeight(); j++)
      {
        for(unsigned int k = 0; k < from.getNbChannels(); k++)
        {
          int value = from.getPixel(i, j, k);
          image->setPixel(i, j, k, value);
        }
      }
    }
    return image;
  }

  template <typename D>
  Image_t<D>* Converter<Image_t<D> >::makeDisplayable(const Image_t<int>& from)
  {
    Image_t<D>* image = new Image_t<D>(from.getWidth(), from.getHeight(), from.getNbChannels());
    
    bool negValue = false;
    int maxValue = 0;
    for(unsigned int i = 0; i < from.getWidth(); i++)
    {
      for(unsigned int j = 0; j < from.getHeight(); j++)
      {
        for(unsigned int k = 0; k < from.getNbChannels(); k++)
        {
          int value = from.getPixel(i, j, k);
          if(!negValue && value < 0) negValue = true;
          if(std::abs(value) > std::abs(maxValue)) maxValue = value;
        }
      }
    }
    int factor = std::abs(maxValue / 255);
    
    /*std::cout << "Max value : " << maxValue << std::endl;*/
    
    for(unsigned int i = 0; i < from.getWidth(); i++)
    {
      for(unsigned int j = 0; j < from.getHeight(); j++)
      {
        for(unsigned int k = 0; k < from.getNbChannels(); k++)
        {
          int newPixel = from.getPixel(i, j, k);
          if(factor != 0)
          {
            newPixel /= factor;
          }
            
          if(negValue)
          {
            newPixel += 127;
            if(newPixel > 255) newPixel = 255;
            else if(newPixel < 0) newPixel = 0;
          }
          image->setPixel(i, j, k, (int)newPixel);
        }
      }
    }
    return image;
  }
  
  template <typename D>
  Image_t<D>* Converter<Image_t<D> >::makeDisplayable(const Image_t<bool>& from)
  {
    Image_t<D>* image = new Image_t<D>(from.getWidth(), from.getHeight(), from.getNbChannels());
    
    for(unsigned int i = 0; i < from.getWidth(); i++)
    {
      for(unsigned int j = 0; j < from.getHeight(); j++)
      {
        for(unsigned int k = 0; k < from.getNbChannels(); k++)
        {
          D value = from.getPixel(i, j, k) ? std::numeric_limits<D>::max() : std::numeric_limits<D>::min();
          image->setPixel(i, j, k, value);
        }
      }
    }
    return image;
  }

}
