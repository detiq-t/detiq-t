#ifndef IMAGEIN_MORPHOMAT_H
#define IMAGEIN_MORPHOMAT_H

#include <vector>
#include <algorithm>

#include "../GenericAlgorithm.h"
#include "../GrayscaleImage.h"
#include "Difference.h"
#include "Otsu.h"
#include "../Converter.h"

namespace imagein {

  namespace MorphoMat {

    template <typename D>
    class StructElem  : public GrayscaleImage_t<bool> {
      public:
        StructElem(std::string filename) {
            Image image(filename);
            algorithm::Otsu algo;
            GrayscaleImage* im_tmp = Converter<GrayscaleImage>::convert(image);
            GrayscaleImage* im_res = algo(im_tmp);
            
            _width = im_res->getWidth();
            _height = im_res->getHeight();
            _mat = new bool[_width * _height * _nChannels];
            
            for(unsigned int j = 0; j < getHeight(); ++j) {
                for(unsigned int i = 0; i < getWidth(); ++i) {
                    setPixel(i, j, (im_res->getPixel(i, j) <= 0));
                }
            }

            _scale = 1;
            _centerX = getWidth()/2;
            _centerY = getHeight()/2;
        }
        StructElem(GrayscaleImage_t<bool> elem, unsigned int centerX, unsigned int centerY) : GrayscaleImage_t<bool>(elem), _scale(1), _centerX(centerX), _centerY(centerY) {}
        inline unsigned char getScale() const { return _scale; }
        inline void setScale(unsigned char scale) { if(scale>0) { _scale = scale; } }
        inline unsigned int getCenterX() { return _centerX; }
        inline unsigned int getCenterY() { return _centerY; }
        inline void setCenterX(unsigned int centerX) { _centerX = centerX; }
        inline void setCenterY(unsigned int centerY) { _centerY = centerY; }
        inline void setCenter(unsigned int centerX, unsigned int centerY) { _centerX = centerX; _centerY = centerY; }
        std::vector<D> intersect(const Image_t<D>& image, unsigned int offsetX, unsigned int offsetY, unsigned int channel) {
            std::vector<D> pixels;
            for(unsigned int j = 0; j < getHeight()*_scale; ++j) {
                for(unsigned int i = 0; i < getWidth()*_scale; ++i) {
                    if(getPixel(i/_scale,j/_scale)) {
                        int x = i - _centerX*_scale + offsetX;        
                        int y = j - _centerY*_scale + offsetY;
                        if(x>=0 && y>=0 && static_cast<unsigned int>(x)<image.getWidth() && static_cast<unsigned int>(y)<image.getHeight()) {
                            pixels.push_back(image.getPixel(static_cast<unsigned int>(x),static_cast<unsigned int>(y),channel));
                        }
                    }
                }
            }
            return pixels;
        }
        void save(const std::string& filename) const {
            GrayscaleImage img(getWidth(), getHeight());
            for(unsigned int j = 0; j < img.getHeight(); ++j) {
                for(unsigned int i = 0; i < img.getWidth(); ++i) {
                    img.setPixel(i, j, getPixel(i, j) ? 0 : 255);
                }
            }
            img.save(filename);
        }
        
      private:
        unsigned char _scale;
        unsigned int _centerX, _centerY;
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
      protected:
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            const Image_t<D>& img = *imgs[0];
            Image_t<D> *result = new Image_t<D>(img.getWidth(), img.getHeight(), img.getNbChannels());

            if(this->_elem.getScale()>1) {
                for(unsigned int channel = 0; channel < img.getNbChannels(); ++channel) {
                    for(unsigned int offsetY = 0; offsetY < img.getHeight(); ++offsetY) {
                        for(unsigned int offsetX = 0; offsetX < img.getWidth(); ++offsetX) {
                           
                            D value = std::numeric_limits<D>::max();
                            
                            for(unsigned int j = 0; j < this->_elem.getHeight()*this->_elem.getScale(); ++j) {
                                for(unsigned int i = 0; i < this->_elem.getWidth()*this->_elem.getScale(); ++i) {
                                    if(this->_elem.getPixel(i/this->_elem.getScale(),j/this->_elem.getScale())) {
                                        const int px = i - this->_elem.getCenterX()*this->_elem.getScale() + offsetX;        
                                        const int py = j - this->_elem.getCenterY()*this->_elem.getScale() + offsetY;
                                        if(px>=0 && py>=0 && static_cast<unsigned int>(px)<img.getWidth() && static_cast<unsigned int>(py)<img.getHeight()) {
                                            if(img.getPixel(static_cast<unsigned int>(px),static_cast<unsigned int>(py),channel) < value) {
                                                value = img.getPixel(static_cast<unsigned int>(px),static_cast<unsigned int>(py),channel);
                                            }
                                        }
                                    }
                                }
                            }
                            result->setPixel(offsetX, offsetY, channel, value);
                        }
                    }
                }
            }
            else {
                for(unsigned int channel = 0; channel < img.getNbChannels(); ++channel) {
                    for(unsigned int offsetY = 0; offsetY < img.getHeight(); ++offsetY) {
                        for(unsigned int offsetX = 0; offsetX < img.getWidth(); ++offsetX) {
                           
                            D value = std::numeric_limits<D>::max();
                            
                            for(unsigned int j = 0; j < this->_elem.getHeight(); ++j) {
                                for(unsigned int i = 0; i < this->_elem.getWidth(); ++i) {
                                    if(this->_elem.getPixel(i,j)) {
                                        const int px = i - this->_elem.getCenterX() + offsetX;        
                                        const int py = j - this->_elem.getCenterY() + offsetY;
                                        if(px>=0 && py>=0 && static_cast<unsigned int>(px)<img.getWidth() && static_cast<unsigned int>(py)<img.getHeight()) {
                                            if(img.getPixel(static_cast<unsigned int>(px),static_cast<unsigned int>(py),channel) < value) {
                                                value = img.getPixel(static_cast<unsigned int>(px),static_cast<unsigned int>(py),channel);
                                            }
                                        }
                                    }
                                }
                            }
                            result->setPixel(offsetX, offsetY, channel, value);
                        }
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
      protected:
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            const Image_t<D>& img = *imgs[0];
            Image_t<D> *result = new Image_t<D>(img.getWidth(), img.getHeight(), img.getNbChannels());

            if(this->_elem.getScale()>1) {
                for(unsigned int channel = 0; channel < img.getNbChannels(); ++channel) {
                    for(unsigned int offsetY = 0; offsetY < img.getHeight(); ++offsetY) {
                        for(unsigned int offsetX = 0; offsetX < img.getWidth(); ++offsetX) {
                           
                            D value = std::numeric_limits<D>::min();
                            
                            for(unsigned int j = 0; j < this->_elem.getHeight()*this->_elem.getScale(); ++j) {
                                for(unsigned int i = 0; i < this->_elem.getWidth()*this->_elem.getScale(); ++i) {
                                    if(this->_elem.getPixel(i/this->_elem.getScale(),j/this->_elem.getScale())) {
                                        const int px = i - this->_elem.getCenterX()*this->_elem.getScale() + offsetX;        
                                        const int py = j - this->_elem.getCenterY()*this->_elem.getScale() + offsetY;
                                        if(px>=0 && py>=0 && static_cast<unsigned int>(px)<img.getWidth() && static_cast<unsigned int>(py)<img.getHeight()) {
                                            if(img.getPixel(static_cast<unsigned int>(px),static_cast<unsigned int>(py),channel) > value) {
                                                value = img.getPixel(static_cast<unsigned int>(px),static_cast<unsigned int>(py),channel);
                                            }
                                        }
                                    }
                                }
                            }
                            result->setPixel(offsetX, offsetY, channel, value);
                        }
                    }
                }
            }
            else {
                for(unsigned int channel = 0; channel < img.getNbChannels(); ++channel) {
                    for(unsigned int offsetY = 0; offsetY < img.getHeight(); ++offsetY) {
                        for(unsigned int offsetX = 0; offsetX < img.getWidth(); ++offsetX) {
                           
                            D value = std::numeric_limits<D>::min();
                            
                            for(unsigned int j = 0; j < this->_elem.getHeight(); ++j) {
                                for(unsigned int i = 0; i < this->_elem.getWidth(); ++i) {
                                    if(this->_elem.getPixel(i,j)) {
                                        const int px = i - this->_elem.getCenterX() + offsetX;        
                                        const int py = j - this->_elem.getCenterY() + offsetY;
                                        if(px>=0 && py>=0 && static_cast<unsigned int>(px)<img.getWidth() && static_cast<unsigned int>(py)<img.getHeight()) {
                                            if(img.getPixel(static_cast<unsigned int>(px),static_cast<unsigned int>(py),channel) > value) {
                                                value = img.getPixel(static_cast<unsigned int>(px),static_cast<unsigned int>(py),channel);
                                            }
                                        }
                                    }
                                }
                            }
                            result->setPixel(offsetX, offsetY, channel, value);
                        }
                    }
                }
            }

            //for(unsigned int k = 0; k < img.getNbChannels(); ++k) {
                //for(unsigned int j = 0; j < img.getHeight(); ++j) {
                    //for(unsigned int i = 0; i < img.getWidth(); ++i) {
                        //std::vector<D> inter = this->_elem.intersect(img, i, j, k);
                        //D value = *max_element(inter.begin(), inter.end());
                        //result->setPixel(i, j, k, value);
                    //}
                //}
            //}

            return result;
        }
    };
    
    template <typename D>
    class Opening : public Operator<D> {
      public:
        Opening(const StructElem<D>& elem) : Operator<D>(elem) {}
      protected:
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            
            const Image_t<D>& img = *imgs[0];

            Erosion<D> erosion(this->_elem);
            Image_t<D>* buffer = erosion(&img);
            Dilatation<D> dilatation(this->_elem);
            Image_t<D>* result = dilatation(buffer);
            delete buffer;

            return result;
        }
    };
    
    template <typename D>
    class Closing : public Operator<D> {
      public:
        Closing(const StructElem<D>& elem) : Operator<D>(elem) {}
      protected:
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            
            const Image_t<D>& img = *imgs[0];

            Dilatation<D> dilatation(this->_elem);
            Image_t<D>* buffer = dilatation(&img);
            Erosion<D> erosion(this->_elem);
            Image_t<D>* result = erosion(buffer);
            delete buffer;

            return result;
        }
    };

    template <typename D>
    class Gradient : public Operator<D> {
      public:
        Gradient(const StructElem<D>& elem) : Operator<D>(elem) {}
      protected:
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
    
    template <typename D>
    class WhiteTopHat : public Operator<D> {
      public:
        WhiteTopHat(const StructElem<D>& elem) : Operator<D>(elem) {}
      protected:
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            
            const Image_t<D>& img = *imgs[0];

            Opening<D> op(this->_elem);
            Image_t<D>* buffer = op(&img);

            algorithm::Difference<Image_t<D> > difference;

            Image_t<D>* result = difference(imgs[0], buffer);
            delete buffer;
            return result;
        }
    };
    
    template <typename D>
    class BlackTopHat : public Operator<D> {
      public:
        BlackTopHat(const StructElem<D>& elem) : Operator<D>(elem) {}
      protected:
        Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) {
            
            const Image_t<D>& img = *imgs[0];

            Closing<D> op(this->_elem);
            Image_t<D>* buffer = op(&img);

            algorithm::Difference<Image_t<D> > difference;

            //Image_t<D>* result = difference(buffer, imgs[0]);
            Image_t<D>* result = new Image_t<D>(img.getWidth(), img.getHeight(), img.getNbChannels());
            typename Image_t<D>::const_iterator it1 = img.begin();
            typename Image_t<D>::const_iterator it2 = buffer->begin();
            typename Image_t<D>::iterator it3 = result->begin();
            unsigned int i =0;
            while(it3 < result->end()) {

                *it3 = *it2 - *it1;
                if(*it1 > *it2) {
                    std::cout << (int)*it2 << ">"  << (int)*it1 << std::endl;
                    ++i;
                }
                ++it1;
                ++it2;
                ++it3;
            }
            delete buffer;
            return result;
        }
    };
  
  }

}

#endif //!IMAGIN_MORPHOMAT_H
