#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include "Rectangle.h"
#include "Histogram.h"

namespace ImageIn
{

    typedef enum {
        F_BMP,
        F_JPG,
        F_PNG,
        F_WEBP
    }ImgFormat;

    template <typename D>
    class Image
    {
        public:
            typedef D* iterator;
            typedef const D* const_iterator;

            Image() : _width(0), _height(0), _nChannels(0) {};
            Image(unsigned int width, unsigned int height, unsigned int nChannels, const D* data);
            Image(std::string filename);

            virtual ~Image() { delete[] _mat; }

            Image(const Image& other);
            Image& operator=(const Image& other);

            inline unsigned int getWidth() const { return _width; }
            inline unsigned int getHeight() const { return _height; }
            inline unsigned int getNbChannels() const { return _nChannels; }

            const D& getPixel(unsigned int x, unsigned int y, unsigned int channel) const;
            void setPixel(unsigned int x, unsigned int y, unsigned int channel, const D& cPixel);
            void setPixel(unsigned int x, unsigned int y, const D* pixel);

            inline iterator begin() { return _mat; }
            inline const_iterator begin() const { return _mat; }
            inline iterator end() { return _mat + _width*_height*_nChannels; }
            inline const_iterator end() const { return _mat + _width*_height*_nChannels; }

            Image<D> crop(const Rectangle& rect) const;

            void save(std::string filename, ImgFormat format) const;

            Histogram getHistogram(unsigned int channel, const Rectangle& rect = Rectangle()) const;

            // TODO (spercott#1#): Image from stl container iterator
            //void setPixel(int x, int y, std::iterator begin, std::iterator end);


        protected:
        private:
            unsigned int _width;
            unsigned int _height;
            unsigned int _nChannels;
            D* _mat;
    };

}


#include "Image.tpp"

#endif // IMAGE_H
