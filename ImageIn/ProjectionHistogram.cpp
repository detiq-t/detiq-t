#include "ProjectionHistogram.h"

using namespace imagein;

template <typename D>
ProjectionHistogram::ProjectionHistogram(const Image<D>& img, D value, bool horizontal, unsigned int channel, const Rectangle& rect) : Array() {
    // We recreate the Array depending on the orientation of the projection and the size of the cropped Image
    if(horizontal) _width = rect.h;
    else _width = rect.w;
    delete [] _array;
    _array = new unsigned int[_width];
    //TODO : vérifier si crop retourne bien une référence (c'est louche), et du coup si c'est pas le cas (pointeur), penser à faire le delete de workImg à la fin de la méthode, et à changer les . en ->
    // We crop the Image to the Rectangle given in parameter
    Image<D> workImg = img.crop(rect);
    // We prepare to iterate through the Image, we get the max width and height now to avoid to calculate it every iteration
    unsigned int wmax, hmax, iterw, iterh;
    wmax = workImg.getWidth();
    hmax = workImg.getHeight();
    for(iterw=0;iterw<wmax;iterw++) {
        for(iterh=0;iterh<hmax;iterh++) {
            if(workImg.getPixel(iterw,iterh,channel)==value) {
                if(horizontal) _array[iterh]++;
                else _array[iterw]++;
            }
        }
    }
}
/*
template <typename D>
ProjectionHistogram:ProjectionHistogram(const Image<D>& img, D value, bool horizontal, const Rectangle& rect) {

}*/
