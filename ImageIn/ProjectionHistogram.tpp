//#include "ProjectionHistogram.h"

template <typename D>
imagein::ProjectionHistogram_t<D>::ProjectionHistogram_t(const Image_t<D>& img, D value, bool horizontal, const Rectangle& rect, unsigned int channel) {
    // We recreate the Array depending on the orientation of the projection and the size of the cropped Image
    if(horizontal) _width = rect.h;
    else _width = rect.w;
    delete [] _array;
    _array = new unsigned int[_width];
    // We crop the Image to the Rectangle given in parameter
    Image_t<D>* workImg = img.crop(rect);
    // We prepare to iterate through the Image, we get the max width and height now to avoid to calculate it every iteration
    unsigned int wmax, hmax, iterw, iterh;
    wmax = workImg->getWidth();
    hmax = workImg->getHeight();
    for(iterw=0;iterw<wmax;iterw++) {
        for(iterh=0;iterh<hmax;iterh++) {
            if(workImg->getPixel(iterw,iterh,channel)==value) {
                if(horizontal) _array[iterh]++;
                else _array[iterw]++;
            }
        }
    }
	delete workImg;
}

template <typename D>
imagein::ProjectionHistogram_t<D>::ProjectionHistogram_t(const Image_t<D>& img, D value, bool horizontal, unsigned int channel) {
	// We recreate the Array depending on the orientation of the projection and the size of the cropped Image
    if(horizontal) _width = img.getHeight();
    else _width = img.getWidth();
    delete [] _array;
    _array = new unsigned int[_width];
    // We prepare to iterate through the Image, we get the max width and height now to avoid to calculate it every iteration
    unsigned int wmax, hmax, iterw, iterh;
    wmax = img.getWidth();
    hmax = img.getHeight();
    for(iterw=0;iterw<wmax;iterw++) {
        for(iterh=0;iterh<hmax;iterh++) {
            if(img.getPixel(iterw,iterh,channel)==value) {
                if(horizontal) _array[iterh]++;
                else _array[iterw]++;
            }
        }
    }
}
