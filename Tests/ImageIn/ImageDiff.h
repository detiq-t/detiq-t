/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

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
