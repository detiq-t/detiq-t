//#include "Filtering.h"

#include "Filtering.h"

#include <algorithm>
#ifdef __linux__
#include <pthread.h>
#include <sys/sysinfo.h>
#endif
#include "Average.h"
#include "Distance.h"

namespace imagein
{
namespace algorithm
{
Filtering::Filtering(Filter* filter)
{
    _filters.push_back(filter);
    _policy = blackPolicy;
}

Filtering::Filtering(std::vector<Filter*> filters) : _filters(filters)
{
    _policy = blackPolicy;
}

Image_t<int>* Filtering::algorithm(const std::vector<const Image_t<int>*>& imgs)
{
    const Image_t<int>* img = dynamic_cast<const Image_t<int>*>(imgs.at(0));

    if(img == NULL) {
        throw ImageTypeException(__LINE__, __FILE__);
    }

    int posFactor = 0;
    int negFactor = 0;

    int width = img->getWidth();
    int height = img->getHeight();
    int nChannels = img->getNbChannels();
    bool odd = width % 2 != 1 || height % 2 != 1;

    std::vector<Filter*>::iterator filter;
    std::vector<Image_t<int>*> images;

    for(filter = _filters.begin(); filter != _filters.end(); ++filter)
    {
        Filter::iterator iter = (*filter)->begin();
        for(; iter != (*filter)->end(); ++iter)
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

        Image_t<int>* result = new Image_t<int>(width, height, nChannels);

#ifdef __linux__

        int numCPU;
#ifdef _SC_NPROCESSORS_ONLN
        numCPU = sysconf( _SC_NPROCESSORS_ONLN );
#else
        numCPU = 1;
#endif
        pthread_t threads[numCPU];

        int inf = 0;
        int step = width / numCPU;
        for(int i = 0; i < numCPU; i++)
        {
            pthread_t thread;
            pthread_attr_t attr;
            pthread_attr_init(&attr);

            struct ParallelArgs* args = new struct ParallelArgs;
            args->img = img;
            args->result = result;
            args->filter = *filter;
            args->policy = _policy;
            args->infx = inf;
            if(i == numCPU - 1)
                args->supx = width;
            else
                args->supx = inf + step;
            args->factor = factor;
            args->odd = odd;

            pthread_create(&thread, &attr, parallelAlgorithm, (void*)args);

            inf = inf + step;
            threads[i] = thread;
        }

        for(int i = 0; i < numCPU; i++)
            pthread_join(threads[i], NULL);

#else
        
        int halfHeightFilter = (*filter)->height() / 2;
        int halfWidthFilter = (*filter)->width() / 2;

        for(int x = 0; x < width; x++)
        {
            for(int y = 0; y < height; y++)
            {
                for(int channel = 0; channel < nChannels; channel++)
                {
                    int newPixel = 0;

                    for(int i = 0; i < (*filter)->width(); i++)
                    {
                        for(int j = 0; j < (*filter)->height(); j++)
                        {
                            if(odd)
                            {
                                newPixel += (**filter)[i][j] * ((*_policy)(img, x + i - halfWidthFilter, y + j - halfHeightFilter, channel));
                            }
                            else
                            {
                                newPixel += (**filter)[i][j] * ((*_policy)(img, x + i - halfWidthFilter - 1, y + j - halfHeightFilter - 1, channel));
                            }
                        }
                    }
                    if(factor > 1)
                        newPixel /= factor;
                    result->setPixel(x, y, channel, newPixel);
                }
            }
        }
#endif
        images.push_back(result);
    }
    Image_t<int>* result = NULL;

    if(images.size() == 1)
        result = images[0];
    else
    {
        unsigned int size = images.size();
        
        MaxDistance<Image_t<int>, 2> av;

        for(unsigned int i = 0; i < size; ++i)
        {
            if(result == NULL)
            {
                result = av(images[0], images[1]);
            }
            else
            {
                result = av(result, images[i]);
            }
        }
    }
    return result;
}

#ifdef __linux__
void* Filtering::parallelAlgorithm(void* data)
{
    struct ParallelArgs args = *((ParallelArgs*) data);

    const Image_t<int>* img = args.img;
    Image_t<int>* result = args.result;
    Filter* filter = args.filter;
    Policy policy = args.policy;
    unsigned int infx = args.infx;
    unsigned int supx = args.supx;
    int factor = args.factor;
    bool odd = args.odd;

    int halfHeightFilter = filter->height() / 2;
    int halfWidthFilter = filter->width() / 2;
    for(unsigned int x = infx; x < supx; x++)
    {
        for(unsigned int y = 0; y < img->getHeight(); y++)
        {
            for(unsigned int channel = 0; channel < img->getNbChannels(); channel++)
            {
                int newPixel = 0;

                for(int i = 0; i < filter->width(); i++)
                {
                    for(int j = 0; j < filter->height(); j++)
                    {
                        int p;
                        if(odd)
                        {
                            p = (*filter)[i][j] * ((*policy)(img, (int)x + i - halfWidthFilter, (int)y + j - halfHeightFilter, channel));
                        }
                        else
                        {
                            p = (*filter)[i][j] * ((*policy)(img, (int)x + i - halfWidthFilter - 1, (int)y + j - halfHeightFilter - 1, channel));
                        }
                        newPixel += p;
                    }
                }
                if(factor > 1)
                    newPixel /= factor;
                result->setPixel(x, y, channel, newPixel);
            }
        }
    }
    delete (ParallelArgs*) data;
    if(supx != img->getWidth())
        pthread_exit(NULL);
}
#endif

Filtering Filtering::uniformBlur(int numPixels = 3)
{
    return Filtering(Filter::uniform(numPixels));
}

Filtering Filtering::gaussianBlur(double alpha)
{
    return Filtering(Filter::gaussian(alpha));
}

Filtering Filtering::prewitt(int numPixels = 3)
{
    return Filtering(Filter::prewitt(numPixels));
}

Filtering Filtering::roberts()
{
    return Filtering(Filter::roberts());
}

Filtering Filtering::sobel()
{
    return Filtering(Filter::sobel());
}

Filtering Filtering::squareLaplacien()
{
    return Filtering(Filter::squareLaplacien());
}
}
}
