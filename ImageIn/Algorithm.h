#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <cstdarg>
#include <typeinfo>

#include "Image.h"
#include "GenericAlgorithm.h"
#include "AlgorithmException.h"

namespace imagein
{
    template < typename D, template <typename D> class I, unsigned int A = 1 >
    class SpecificAlgorithm_t : public GenericAlgorithm_t<D, A> {
        public:
            
            inline I<D>* operator() (const std::vector<const Image_t<D>*>& imgs) const {
                if(imgs.size()!=A) throw NotEnoughImageException(__LINE__, __FILE__);
                return algorithm(imgs);
            }
        
        protected:
            virtual I<D>* algorithm(const std::vector<const Image_t<D>*>&) const = 0;
    };


    template < typename D, template <typename D> class I, unsigned int A = 1 >
    class Algorithm_t : public SpecificAlgorithm_t<D, I, A> {
        
    };

    
    template <typename D, template <typename D> class I>
    class Algorithm_t<D,I,1> : public SpecificAlgorithm_t<D,I,1> {
        public:
        inline I<D>* operator() (const Image_t<D>* img) const { 
            std::vector<const Image_t<D>*> imgs;
            imgs.push_back(img);
            return this->algorithm(imgs);
        }
    };

    template <typename D, template <typename D> class I>
    class Algorithm_t<D,I,2> : public SpecificAlgorithm_t<D,I,2> {
        public:
        inline I<D>* operator() (const Image_t<D>* img, const Image_t<D>* img2) const { 
            std::vector<const Image_t<D>*> imgs;
            imgs.push_back(img);
            imgs.push_back(img2);
            return this->algorithm(imgs);
        }
    };

    template <typename D, template <typename D> class I>
    class Algorithm_t<D,I,3> : public SpecificAlgorithm_t<D,I,3> {
        public:
        inline I<D>* operator() (const Image_t<D>* img, const Image_t<D>* img2, const Image_t<D>* img3) const { 
            std::vector<const Image_t<D>*> imgs;
            imgs.push_back(img);
            imgs.push_back(img2);
            imgs.push_back(img3);
            return this->algorithm(imgs);
        }
    };


    template <template <typename D> class I, unsigned int A=1 >
    class Algorithm_8 : public Algorithm_t<uint8_t, I, A> {};

    template <template <typename D> class I, unsigned int A=1 >
    class Algorithm_16 : public Algorithm_t<uint16_t, I, A> {};

    template <template <typename D> class I, unsigned int A=1 >
    class Algorithm_32 : public Algorithm_t<uint32_t, I, A> {};


}

#endif //!ALGORITHM_H
