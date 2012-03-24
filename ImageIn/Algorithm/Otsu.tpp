//#include "Otsu.h"

#include "../Histogram.h"

#include <limits>

using namespace std;
using namespace imagein;
using namespace imagein::algorithm;

template <typename D>
GrayscaleImage_t<D>* Otsu_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
{
    const GrayscaleImage_t<D>* img = dynamic_cast<const GrayscaleImage_t<D>*>(imgs.at(0));

    if(img == NULL) {
        throw ImageTypeException(__LINE__, __FILE__);
    }

    _threshold = computeThreshold(img);

    D* data = new D[img->getWidth() * img->getHeight()];
    D* out = data;
    for(typename GrayscaleImage_t<D>::const_iterator it = img->begin() ; it != img->end() ; ++it) {
        *(out++) = (*it < _threshold) ? 0 : numeric_limits<D>::max();
    }

    return new GrayscaleImage_t<D>(img->getWidth(), img->getHeight(), data);
}

template<typename D>
D Otsu_t<D>::computeThreshold(const GrayscaleImage_t<D>* img)
{
    //Compute histogram of the image probability of each value.
    Histogram hist = img->getHistogram();
    
    unsigned int nPixel = img->getWidth() * img->getHeight(); 

    //Compute intra-class variance for each possible threshold, and chose the minimum
    int weightb = 0;
    int weightw = 0;
    double sumb = 0;
    double sum = 0;
    for(unsigned int i = 0 ; i < 1<<sizeof(D)*8 ; ++i) {
        sum += i*hist[i];
    }

    double maxVariance = 0;
    unsigned int chosenThreshold = 0;
    for(unsigned int thresh = 0 ; thresh < 1<<sizeof(D)*8; ++thresh) {

        weightb += hist[thresh];
        if(weightb == 0) continue;

        weightw = nPixel - weightb;
        if(weightw == 0) break;

        sumb += thresh*hist[thresh];
        
        double meanb = sumb / static_cast<double>(weightb);
        double meanw = (sum - sumb) / static_cast<double>(weightw);

        double variance = static_cast<double>(weightb) * static_cast<double>(weightw) * (meanb - meanw) * (meanb - meanw);

        //if this variance is lower greater than previous maximum, replace previous threshold with this one.
        //Always replace if this is the first threshold tried.
        if (variance > maxVariance) {
            maxVariance = variance;
            chosenThreshold = thresh;
        }
    }

    return chosenThreshold;
}
