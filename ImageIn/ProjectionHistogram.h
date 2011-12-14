#ifndef PROJECTIONHISTOGRAM_H
#define PROJECTIONHISTOGRAM_H


#include "Array.h"
#include "Image.h"


namespace imagein
{
    class ProjectionHistogram : public Array
    {
        public:
            template <typename D>
            ProjectionHistogram(const Image<D>& img, unsigned int channel, const Rectangle& rect);
            template <typename D>
            ProjectionHistogram(const Image<D>& img, const Rectangle& rect);
            virtual ~ProjectionHistogram();
        protected:
        private:
    };
}


#endif // PROJECTIONHISTOGRAM_H
