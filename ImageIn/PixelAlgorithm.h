#ifndef PIXELALGORITHM_H
#define PIXELALGORITHM_H

#include <vector>

#include "Algorithm.h"

namespace imagein
{
    template <typename D, template <typename D> class I, unsigned int A=1>
    class PixelAlgorithm_t : public Algorithm_t<D, I, A> {

        protected:

            virtual D pixelOp(D pixel[A]) const = 0; 

            I<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) const {

                for(typename std::vector<const Image_t<D>*>::const_iterator it = imgs.begin(); it < imgs.end(); ++it) {
                    if((*it)->end()-(*it)->begin()!=imgs[0]->end()-imgs[0]->begin()) {
                        throw ImageSizeException(__LINE__, __FILE__);
                    }
                }

                I<D>* result = new I<D>(imgs[0]->getWidth(), imgs[0]->getHeight());
                typename Image_t<D>::const_iterator iIt[A];
                for(int i=0; i<A; ++i) iIt[i] = imgs[i]->begin();
                typename I<D>::iterator oIt = result->begin();
                D pixels[A];

                while(oIt < result->end()) {
                    for(int i=0; i<A; ++i) pixels[i] = *iIt[i];
                    *oIt = pixelOp(pixels);
                    ++oIt;
                    for(int i=0; i<A; ++i) ++iIt[i];
                }

                return result;
            }
    };

    //template <typename D, template <typename D> class I, unsigned int A>
    //class PixelAlgorithm_t : public _PixelAlgorithm_t<D, I, A> {
    //};
    
    //template <typename D, template <typename D> class I>
    //class PixelAlgorithm_t<D, I, 1> : public _PixelAlgorithm_t<D, I, 1> {

            //virtual D pixelOp(D pixel[1]) const {
                //return pixelOp(pixel[0]);
            //}

            //virtual D pixelOp(D p1) const = 0;

    //};

    //template <typename D, template <typename D> class I>
    //class PixelAlgorithm_t<D, I, 2> : public _PixelAlgorithm_t<D, I, 2> {

            //virtual D pixelOp(D pixel[2]) const {
                //return pixelOp(pixel[0], pixel[1]);
            //}

            //virtual D pixelOp(D p1, D p2) const = 0;
    //};

    //template <typename D, template <typename D> class I>
    //class PixelAlgorithm_t<D, I, 3> : public _PixelAlgorithm_t<D, I, 3> {

            //virtual D pixelOp(D pixel[3]) const {
                //return pixelOp(pixel[0], pixel[1], pixel[2]);
            //}
            
            //virtual D pixelOp(D p1, D p2, D p3) const = 0;
    //};
}

#endif //!PIXELALGORITHM_H
