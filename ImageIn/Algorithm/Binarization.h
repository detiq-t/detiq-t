#ifndef BINARIZATION_H
#define BINARIZATION_H

#include "../Image.h"
#include "../GrayscaleImage.h"
#include "../Algorithm.h"

namespace imagein 
{

    template <typename D>
    class Binarization_t : public Algorithm_t<GrayscaleImage_t<D>, 1>
    {
        public:
            Binarization_t(D threshold) 
              : _threshold(threshold), _threshold2(0), _blackBand(false) {};
            Binarization_t(D infThreshold, D supThreshold, bool blackBand = false) 
              : _threshold(infThreshold), _threshold2(supThreshold), _blackBand(blackBand) {};

        protected:

            /*! Implementation of the algorithm.
             * 
             * see the documentation of GenericAlgorithm_t, SpecificAlgorithm_t and Algorithm_t for
             * informations on the Algorithm interface.
             */
            GrayscaleImage_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) const;
        
        private:
            D _threshold;
            D _threshold2;
            bool _blackBand;
    };

    typedef Binarization_t<depth_default_t> Binarization; //!< Standard Algorithm with default depth. See Image_t::depth_default_t
}

#include "Binarization.tpp"

#endif
