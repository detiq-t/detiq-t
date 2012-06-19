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

#ifndef OTSU_H
#define OTSU_H

#include "../Image.h"
#include "../GrayscaleImage.h"
#include "../Algorithm.h"

namespace imagein 
{
    namespace algorithm
    {
        /*!
         * \brief This is an implementation of the Otsu thresholding algorithm.
         * 
         * Otsu is a binarization algorithm. The threshold is calculated using the Between-class variance
         * between Foreground and Background. The threshold inducing the greatest variance is used to 
         * binarize the image.
         *
         * Explanation of the algorithm : http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
         *
         * Arity : 1 \n
         * Input type : GrayscaleImage_t<D> \n
         * Output type : GraysaleImage_t<D> \n
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
                static D computeThreshold(const GrayscaleImage_t<D>* img);
                
                /*!
                 * \brief Returns the threshold used by the last application of the algorithm
                 *
                 * This method can be used after the application of the algorithm on an image to retrieve the
                 * threshold used. Only the last threshold can be retrieved.
                 *
                 * \return the last threshold used.
                 */
                D getThreshold() { return _threshold; }

            protected:

                /*! Implementation of the algorithm.
                 * 
                 * see the documentation of GenericAlgorithm_t, SpecificAlgorithm_t and Algorithm_t for
                 * informations on the Algorithm interface.
                 */
                GrayscaleImage_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
            
            private:
                D _threshold;
        };

        typedef Otsu_t<depth_default_t> Otsu; //!< Standard Algorithm with default depth. See Image_t::depth_default_t
    }
}
#include "Otsu.tpp"

#endif
