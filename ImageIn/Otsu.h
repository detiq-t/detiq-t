#ifndef OTSU_H
#define OTSU_H

#include "Image.h"
#include "GrayscaleImage.h"
#include "Algorithm.h"

namespace imagein 
{

    /*!
     * \brief This is an implementation of the Otsu thresholding algorithm.
     * 
     * Otsu is a binarization algorithm. The threshold is calculated using the Between-class variance
     * between Foreground and Background. The threshold inducing the greatest variance is used to 
     * binarize the image.
     *
     * Arity : 1
     * Input type : GrayscaleImage_t<D>
     * Output type : GraysaleImage_t<D>
     *
     * Explanation of the algorithm : http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
     * Complexity : O(n*m) with n and m being the width and height of the image.
     *
     * \tparam D the depth of the input and output image
     */
    template <typename D>
    class Otsu_t : public Algorithm_t<GrayscaleImage_t<D>, 1>
    {
        public:
            //! Default constructor. Does nothing useful.
            Otsu_t() : _threshold(0) {};
            
            /*!
             * \brief Computes the threshold for an image.
             *
             * This method is the core of the algorithm. It is used by operator() but can be used
             * in other context to compute a threshold without actually binarizing the image.
             *
             * \param img The image for which to compute the threshold.
             * \return the threshold calculated.
             */
            static unsigned int computeThreshold(const GrayscaleImage_t<D>* img);
            
            /*!
             * \brief Returns the threshold used by the last application of the algorithm
             *
             * This method can be used after the application of the algorithm on an image to retrieve the
             * threshold used. Only the last threshold can be retrieved.
             *
             * \return the last threshold used.
             */
            unsigned int getLastApplicationThreshold() { return _threshold; }

        protected:

            /*! Implementation of the algorithm.
             * 
             * see the documentation of GenericAlgorithm_t, SpecificAlgorithm_t and Algorithm_t for
             * informations on the Algorithm interface.
             */
            GrayscaleImage_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) const;
        
        private:
            unsigned int _threshold;
    };

    typedef Otsu_t<depth_default_t> Otsu; //!< Standard Algorithm with default depth. See Image_t::depth_default_t
}

#include "Otsu.tpp"

#endif
