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


     * There are two template parameters for this class :
     * -# D is a typename and corresponds to the Depth template parameter of the classe Image_t.
     * -# A is an unsigned integer and corresponds to the Arity of the algorithm, i.e. the number of images the algorithm takes as parameters.
     *
     * As a representation of an algorithm this classe is a class type functor and so it overloads the function call operator.
     * The function call operator is also the only accessible method of this interface and it returns the result of the algorithm method.
     * Any class implementing this interface must define the method named algorithm which describe the comportment of the algorithm.
     *
     * Any class implementing this interface must define the method named algorithm which describe the comportment of the algorithm.
     *
     */
    template <typename D, unsigned int A = 1>
    class GenericAlgorithm_t {
        public:
            inline Image_t<D>* operator() (const std::vector<const Image_t<D>*>& imgs) const;
        protected:
            virtual Image_t<D>* algorithm(const std::vector<const Image_t<D>*>&) const = 0;
    };
}

#include "GenericAlgorithm.tpp"

#endif //!GENERICALGORITHM_H
