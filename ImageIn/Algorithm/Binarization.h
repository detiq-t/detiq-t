#ifndef BINARIZATION_H
#define BINARIZATION_H

#include "../Image.h"
#include "../GrayscaleImage.h"
#include "../Algorithm.h"

namespace imagein 
{
    namespace algorithm
    {
        /*!
         * \brief This is a simple binarization algorithm.
         * 
         * This algorithm will binarize your image using manual thresholds provided when you create the algorithm.
         * You can either provide one threshold (pixels with value < threshold will be black, other pixels will be white)
         * or you can provide two thresholds.
         *
         * If you provide two thresholds, the pixels with value between the two thresholds will be white, other pixels will be black.
         * If you want to invert this behavior, you can do so at construction.
         *
         * Arity : 1 \n
         * Input type : GrayscaleImage_t<D> \n
         * Output type : GraysaleImage_t<D> \n
         * Complexity : O(n*m) with n and m being the width and height of the image.
         *
         * \tparam D the depth of the input and output image
         */
        template <typename D>
        class Binarization_t : public Algorithm_t<GrayscaleImage_t<D>, 1>
        {
            public:
                /*!
                 * \brief Constructor for one threshold.
                 *
                 * This constructs an algorithm with one threshold. Pixels with value < threshold will be black, other will be white.
                 *
                 * \param threshold The threshold to use for binarization.
                 */
                Binarization_t(D threshold) 
                  : _threshold(threshold), _threshold2(0), _blackBand(false) {};
                
                /*!
                 * \brief Constructor for two thresholds.
                 *
                 * This constructs an algorithm with two threshold. Pixels with value between the two threshold will be white, other will be black.
                 * This behavior can be inverted with the third parameter.
                 *
                 * \param infThreshold The lower bound of the white band.
                 * \param supThreshold The greater bound of the white band.
                 * \param blackBand If set to true, the pixels with value between the two thresholds will be black, other will be white.
                 */
                Binarization_t(D infThreshold, D supThreshold, bool blackBand = false) 
                  : _threshold(infThreshold), _threshold2(supThreshold), _blackBand(blackBand) {};

            protected:

                /*! Implementation of the algorithm.
                 * 
                 * see the documentation of GenericAlgorithm_t, SpecificAlgorithm_t and Algorithm_t for
                 * informations on the Algorithm interface.
                 */
                GrayscaleImage_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
            
            private:
                D _threshold;
                D _threshold2;
                bool _blackBand;
        };

        typedef Binarization_t<depth_default_t> Binarization; //!< Standard Algorithm with default depth. See Image_t::depth_default_t
    }
}

#include "Binarization.tpp"

#endif
