#ifndef IMAGEDIFF_H
#define IMAGEDIFF_H

#include <limits>
#include <string>
#include <sstream>

#include <Image.h>
#include <AlgorithmException.h>

template<typename D>
struct ImageDiff {
    ImageDiff(D min_, D max_, double mean_) 
        : total(0), min(min_), max(max_), mean(mean_) {}

    ImageDiff(const imagein::Image_t<D>& img1, const imagein::Image_t<D>& img2) {
        if(img1.getNbChannels() != img2.getNbChannels()
        || img1.getWidth()!=img2.getWidth()
        || img1.getHeight() != img2.getHeight()) {
            throw imagein::ImageSizeException(__LINE__, __FILE__);
        }
        total = 0;
        uintmax_t count = 0;
        max = 0;
        min = std::numeric_limits<D>::max();
        for(typename imagein::Image_t<D>::const_iterator it = img1.begin(), jt = img2.begin(); it < img1.end() && jt < img2.end(); ++it, ++jt) {
             unsigned int diff = std::abs(*it - *jt);
             if(diff > max) max = diff;
             if(diff < min) min = diff;
             total += diff;
             ++count;
        }
        mean = static_cast<double>(total) / count;
    
    }

    bool operator<=(const ImageDiff<D>& diff) const {
       if(this->min > diff.min) return false;
       if(this->max > diff.max) return false;
       return this->mean <= diff.mean;
    }

    std::string toString() {
        if(total==0) return "";
        std::ostringstream oss;
        oss << "Image diff = " << "min:" << (int)min << ", max:" << (int)max << ", mean:" << mean;
        return oss.str();
    }

    uintmax_t total;
    D min;
    D max;
    double mean;
    
};

#endif //!IMAGEDIFF_H
