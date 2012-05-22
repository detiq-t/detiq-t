#ifndef IMAGEIN_MORPHOMAT_H
#define IMAGEIN_MORPHOMAT_H

#include <vector>
#include <algorithm>

#include "../GenericAlgorithm.h"
#include "../GrayscaleImage.h"
#include "Difference.h"

namespace imagein {

  namespace MorphoMat {

    template <typename D>
    class StructElem {
      public:
        StructElem(GrayscaleImage_t<bool> elem, unsigned int centerX, unsigned int centerY) : _elem(elem), _centerY(centerY), _centerX(centerX), _scale(1) {}
        GrayscaleImage_t<bool> getElem() const { return _elem; }
        unsigned char getScale() const { return _scale; }
        void setScale(unsigned char scale) { if(scale>0) { _scale = scale; } }
        std::vector<D> intersect(const Image_t<D>& image, unsigned int offsetX, unsigned int offsetY, unsigned int channel) {
            std::vector<D> pixels;
            for(unsigned int j = 0; j < _elem.getHeight()*_scale; ++j) {
                for(unsigned int i = 0; i < _elem.getWidth()*_scale; ++i) {
                    if(_elem.getPixel(i/_scale,j/_scale)) {
                        int x = i - _centerX*_scale + offsetX;        
                        int y = j - _centerY*_scale + offsetY;
                        if(x>=0 && y>=0 && x<image.getWidth() && y<image.getHeight()) {
                            pixels.push_back(image.getPixel(x,y,channel));
                        }
                    }
                }
            }
            return pixels;
        }
      private:
        unsigned char _scale;
        unsigned int _centerX, _centerY;
        GrayscaleImage_t<bool> _elem;
    };

    template <typename D>
    class Operator : public GenericAlgorithm_t<D> {
      public:
        Operator(const StructElem<D>& elem) : _elem(elem) {}
      protected:
        StructElem<D> _elem;
    };

    template <typename D>
    class Erosion : public Operator<D> {
      public:
        Erosion(const StructElem<D>& elem) : Operator<D>(elem) {}
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            const Image_t<D>& img = *imgs[0];
            Image_t<D> *result = new Image_t<D>(img.getWidth(), img.getHeight(), img.getNbChannels());

            for(unsigned int k = 0; k < img.getNbChannels(); ++k) {
                for(unsigned int j = 0; j < img.getHeight(); ++j) {
                    for(unsigned int i = 0; i < img.getWidth(); ++i) {
                        std::vector<D> inter = this->_elem.intersect(img, i, j, k);
                        D value;
                        if(inter.size()==0) {
                            //std::cout << "Empty intersection ! " << i << ":" << j << ":" << k << std::endl;
                            value = std::numeric_limits<D>::min();
                        }
                        else {
                            value = *min_element(inter.begin(), inter.end());
                        }
                        result->setPixel(i, j, k, value);
                    }
                }
            }

            return result;
        }
    };
    
    template <typename D>
    class Dilatation : public Operator<D> {
      public:
        Dilatation(const StructElem<D>& elem) : Operator<D>(elem) {}
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            const Image_t<D>& img = *imgs[0];
            Image_t<D> *result = new Image_t<D>(img.getWidth(), img.getHeight(), img.getNbChannels());

            for(unsigned int k = 0; k < img.getNbChannels(); ++k) {
                for(unsigned int j = 0; j < img.getHeight(); ++j) {
                    for(unsigned int i = 0; i < img.getWidth(); ++i) {
                        std::vector<D> inter = this->_elem.intersect(img, i, j, k);
                        D value = *max_element(inter.begin(), inter.end());
                        result->setPixel(i, j, k, value);
                    }
                }
            }

            return result;
        }
    };
    
    template <typename D>
    class Opening : public Operator<D> {
      public:
        Opening(const StructElem<D>& elem) : Operator<D>(elem) {}
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            
            const Image_t<D>& img = *imgs[0];

            Erosion<D> erosion(this->_elem);
            Image_t<D>* buffer = erosion(&img);
            Dilatation<D> dilatation(this->_elem);
            Image_t<D>* result = dilatation(&buffer);
            delete buffer;

            return result;
        }
    };
    
    template <typename D>
    class Closing : public Operator<D> {
      public:
        Closing(const StructElem<D>& elem) : Operator<D>(elem) {}
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            
            const Image_t<D>& img = *imgs[0];

            Dilatation<D> dilatation(this->_elem);
            Image_t<D>* buffer = dilatation(&img);
            Erosion<D> erosion(this->_elem);
            Image_t<D>* result = erosion(&buffer);
            delete buffer;

            return result;
        }
    };

    template <typename D>
    class Gradient : public Operator<D> {
      public:
        Gradient(const StructElem<D>& elem) : Operator<D>(elem) {}
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            
            const Image_t<D>& img = *imgs[0];

            Dilatation<D> dilatation(this->_elem);
            Image_t<D>* bufferd = dilatation(&img);
            Erosion<D> erosion(this->_elem);
            Image_t<D>* buffere = erosion(&img);

            algorithm::Difference<Image_t<D> > difference;

            Image_t<D>* result = difference(bufferd, buffere);
            delete bufferd;
            delete buffere;
            return result;
        }
    };
  
  }

}

#endif //!IMAGIN_MORPHOMAT_H
