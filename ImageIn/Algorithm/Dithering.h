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

#ifndef DITHERING_H
#define DITHERING_H

#include "../Image.h"
#include "../GrayscaleImage.h"
#include "../Algorithm.h"

#include <limits>

namespace imagein 
{
    namespace algorithm
    {
        /*!
         * \brief This is a Floyd-Steinberg dithering algorithm.
         * 
         * This algorithm will binarize your image using the Floyd-Steinberg error diffusion process. The threshold used is the 
         * media value for the pixel depth. Whenever a pixel is set to 0 or 255, the error is reported to surrounding pixels, thus 
         * trying to minimize visual artifacts. The binarized image will represent more closely the original image than a basic 
         * binarization algorithm such as Otsu.
         *
         * Arity : 1 \n
         * Input type : GrayscaleImage_t<D> \n
         * Output type : GraysaleImage_t<D> \n
         * Complexity : O(n*m) with n and m being the width and height of the image.
         *
         * \tparam D the depth of the input and output image
         */
        template <typename D>
        class Dithering_t : public Algorithm_t<Image_t<D>, 1>
        {
            public:
                /*!
                 * \brief Default constructor.
                 *
                 */
                Dithering_t() 
                  : _threshold(std::numeric_limits<D>::max()/2){}; 

            protected:

                /*! Implementation of the algorithm.
                 * 
                 * see the documentation of GenericAlgorithm_t, SpecificAlgorithm_t and Algorithm_t for
                 * informations on the Algorithm interface.
                 */
                Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
            
            private:
                D _threshold;

                struct DiffusionMatrix
                {
                    int width;
                    int height;
                    int total;
                    int center;
                    int* tab;
                        
                    ~DiffusionMatrix() { delete[] tab; }
                };

                static DiffusionMatrix* floydSteinberg();
        };

        typedef Dithering_t<depth_default_t> Dithering; //!< Standard Algorithm with default depth. See Image_t::depth_default_t
        
        
    }
}
#include "Dithering.tpp"

#endif
