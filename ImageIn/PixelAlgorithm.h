#ifndef PIXELALGORITHM_H
#define PIXELALGORITHM_H

#include <vector>

#include "Algorithm.h"
#include "Converter.h"

namespace imagein
{
    /*!
     * \brief PixelAlgorithm_t is a specialized Algorithm_t
     * This class is used to describe algorithm where the nth pixel of the output image only depends of the nth pixels of the input images.
     * 
     * \tparam D A typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam I A templated class representing an Image type such as RgbImage_t. This classe will take the first template parameter D as its template parameter.
     * \tparam A An unsigned integer corresponding to the Arity of the algorithm, i.e. the number of images the algorithm takes as parameters
     *
     * Unline Algorithm_t the method algorithm is implemented, the user of PixelAlgorithm_t must define another method called pixelOp.
     * The pixelOp method specify the operation to do with the pixels of the input images to obtain the pixel of the output image.
     * The algorithm method go through each pixel of the resulting image and set them using pixelOp.
     */
    template <class I, unsigned int A=1>
    class PixelAlgorithm_t : public Algorithm_t<I, A> {

        protected:
            typedef typename I::depth_t D;
            /*!
             * \brief The operation to apply to the input images' pixels in order to obtain the output image's pixel
             * \param pixels The pixels of the input images.
             * \return The pixel of the output image.
             */
            virtual D pixelOp(D pixels[A]) const = 0; 

            /*!
             * \brief The algorithm method here is implemented, you're not supposed to overload it.
             *
             * \throw ImageSizeException if the input images are not all the same size.
             */
            I* algorithm(const std::vector<const Image_t<D>*>& imgs) {

                for(typename std::vector<const Image_t<D>*>::const_iterator it = imgs.begin(); it < imgs.end(); ++it) {
                    if((*it)->end()-(*it)->begin()!=imgs[0]->end()-imgs[0]->begin()) {
                        throw ImageSizeException(__LINE__, __FILE__);
                    }
                }

                Image_t<D>* result = new Image_t<D>(imgs[0]->getWidth(), imgs[0]->getHeight(), imgs[0]->getNbChannels());
                typename Image_t<D>::const_iterator iIt[A];
                for(unsigned int i=0; i<A; ++i) iIt[i] = imgs[i]->begin();
                typename I::iterator oIt = result->begin();
                D pixels[A];

                while(oIt < result->end()) {
                    for(unsigned int i=0; i<A; ++i) pixels[i] = *iIt[i];
                    *oIt = pixelOp(pixels);
                    ++oIt;
                    for(unsigned int i=0; i<A; ++i) ++iIt[i];
                }
                //result->save("tmp.png");

                I* finalResult = Converter<I>::convert(*result);

                return finalResult;
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
