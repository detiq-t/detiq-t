#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Array.h"
#include "Rectangle.h"


namespace imagein
{
    template <typename D>
    class Image_t;

    class Histogram : public Array
    {
        public:
            template <typename D>
            Histogram(const Image_t<D>& img, unsigned int channel, const Rectangle& rect);
            template <typename D>
            Histogram(const Image_t<D>& img, const Rectangle& rect);
        protected:
        private:
    };
}

#include "Histogram.tpp"

#endif // HISTOGRAM_H
