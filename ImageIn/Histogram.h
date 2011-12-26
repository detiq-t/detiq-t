#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "Array.h"
#include "Rectangle.h"


namespace imagein
{
    template <typename D>
    class Image;

    class Histogram : public Array
    {
        public:
            template <typename D>
            Histogram(const Image<D>& img, unsigned int channel, const Rectangle& rect);
            template <typename D>
            Histogram(const Image<D>& img, const Rectangle& rect);
        protected:
        private:
    };
}

#include "Histogram.tpp"

#endif // HISTOGRAM_H
