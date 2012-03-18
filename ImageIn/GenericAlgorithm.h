#ifndef GENERICALGORITHM_H
#define GENERICALGORITHM_H

#include "Image.h"
#include "AlgorithmException.h"

namespace imagein
{
    /*!
     * \brief GenericAlgorithm_t is the top-level interface for all the algorithm
     *
     * This class is abstract, and is an interface to all the concrete classes representing algorithms.
     *
     * \tparam D a typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam A an unsigned integer corresponding to the Arity of the algorithm, i.e. the number of images the algorithm takes as parameters
     * 
     * As a representation of an algorithm this classe is a class type functor and so it overloads the function call operator.
     * The function call operator is also the only accessible method of this interface and it returns the result of the algorithm method.
     * Any class implementing this interface must define the method named algorithm which describe the comportment of the algorithm.
     *
     */
    template <typename D, unsigned int A = 1>
    class GenericAlgorithm_t {
        public:
            /*!
             * \brief Function call operator used to apply the algorithm to a vector of images.
             * It checks the size of the vector and return the result of the algorithm method.
             *
             * \param imgs The vector of images on which the algorithm will be applied. The size of this vector must be equal to A.
             * \return The image resulting of the application of the algorithm.
             * \throw NotEnoughImageException if the size of the vector imgs in not equal to the Arity of the algorithm. 
             * \throw ImageTypeException if implemented in algorithm
             * \throw ImageSizeException if implemented in algorithm
             */
            inline Image_t<D>* operator() (const std::vector<const Image_t<D>*>& imgs) const;
        protected:
            /*!
             * \brief The concrete implementation of the algorithm
             *
             * \param imgs The vector of images on which the algorithm will be applied. The size of this vector must be equal to A.
             * \return The image resulting of the application of the algorithm.
             * \throw ImageTypeException if implemented
             * \throw ImageSizeException if implemented
             */
            virtual Image_t<D>* algorithm(const std::vector<const Image_t<D>*>&) const = 0;
    };
}

#include "GenericAlgorithm.tpp"

#endif //!GENERICALGORITHM_H
