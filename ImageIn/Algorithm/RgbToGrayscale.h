#ifndef ALGO_RGBTOGRAYSCALE_H
#define ALGO_RGBTOGRAYSCALE_H

#include "../Image.h"
#include "../GrayscaleImage.h"
#include "../Algorithm.h"
#include "../RgbImage.h"

#include <vector>
#include <list>
#include <map>

namespace imagein 
{
    namespace algorithm
    {
        /*!
         * \brief RGB to Grayscale.
         * 
         * This algorithm convert an RGB image to a Grayscale image
         *
		 * gray = (0.299*R + 0.587*G + 0.114*B);
         *
         * Arity : 1 \n
         * Input type :  RgbImage_t<D> \n
         * Output type : GrayscaleImage_t<D> \n
         * Complexity : O(n*m) with n and m being the width and height of the image.
         *
         * \tparam D the depth of the input and output image
         */
        template <typename D>
        class RgbToGrayscale_t : public Algorithm_t<Image_t<D>, 1>
        {
            public:
				
                /*!
                 * \brief Default constructor. Allows to specify the parameters of the algorithm.
                 */
                RgbToGrayscale_t()
                    : _r(0.299), _g(0.587), _b(0.114) {}

                RgbToGrayscale_t(double redFactor, double greenFactor, double blueFactor)
                    : _r(redFactor), _g(greenFactor), _b(blueFactor) {}

            protected:

                /*! Implementation of the algorithm.
                 * 
                 * see the documentation of GenericAlgorithm_t, SpecificAlgorithm_t and Algorithm_t for
                 * informations on the Algorithm interface.
                 */
                Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
            
            private:
				
				double _r;
				double _g;
				double _b;

        };

        typedef RgbToGrayscale_t<depth_default_t> RgbToGrayscale; //!< Standard Algorithm with default depth. See Image_t::depth_default_t
    }
}
#include "RgbToGrayscale.tpp"

#endif
