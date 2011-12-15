#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include "Rectangle.h"
#include "Histogram.h"

namespace imagein
{

    template <typename D>
    class Image
    {
        public:
            typedef D* iterator;
            typedef const D* const_iterator;

            Image() : _width(0), _height(0), _nChannels(0), _mat(NULL) {};
            Image(unsigned int width, unsigned int height, unsigned int nChannels);
            Image(unsigned int width, unsigned int height, unsigned int nChannels, const D* data);
            Image(std::string filename);

            virtual ~Image() { delete[] _mat; };

            Image(const Image& other);
            Image& operator=(const Image& other);

            inline unsigned int getWidth() const { return _width; };
            inline unsigned int getHeight() const { return _height; };
            inline unsigned int getNbChannels() const { return _nChannels; };

            const D& getPixel(unsigned int x, unsigned int y, unsigned int channel) const { return _mat[y*_nChannels*_width + x*_nChannels + channel]; };
            void setPixel(unsigned int x, unsigned int y, unsigned int channel, const D& cPixel);
            void setPixel(unsigned int x, unsigned int y, const D* pixel);

            //! Returns an iterator to the first channel on the top-left corner of the image
            inline iterator begin() { return _mat; };
            //! Returns a const iterator to the first channel on the top-left corner of the image
            inline const_iterator begin() const { return _mat; };
            //! Returns an iterator past then end of the image
            inline iterator end() { return _mat + _width*_height*_nChannels; };
            //! returns a const iterator past the end of the image
            inline const_iterator end() const { return _mat + _width*_height*_nChannels; };

            /*!
             * \brief Crops the image to the boundaries defined by a Rectangle.
             *
             * \param rect the rectangle used to define the boundaries of the new image.
             * \return A new image of the same type.
             */
            Image<D> crop(const Rectangle& rect) const;

            void save(std::string filename) const;

            inline Histogram getHistogram(unsigned int channel, const Rectangle& rect = Rectangle()) const { return Histogram(*this, channel, rect); };

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
