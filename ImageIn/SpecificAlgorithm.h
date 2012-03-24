#ifndef SPECIFICALGORITHM_H
#define SPECIFICALGORITHM_H

#include <vector>

#include "Image.h"
#include "GenericAlgorithm.h"
#include "AlgorithmException.h"

namespace imagein
{
    /*!
     * \brief SpecificAlgorithm_t is a specification of the GenericAlgorithm_t 
     *
     * This class is abstract, and is an interface to all the concrete non-generic classes representing algorithms.
     *
     * \tparam D A typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam I A templated class representing an Image type such as RgbImage_t. This classe will take the first template parameter D as its template parameter.
     * \tparam A An unsigned integer corresponding to the Arity of the algorithm, i.e. the number of images the algorithm takes as parameters
     *
     * As a specification of the GenericAlgorithm_t class, SpecificAlgorithm_t only specify the covariant return type of the algorithm's operations.
     * As a result of which the template parameter I must be an unambiguous and accessible direct or indirect derivation of Image_t.
     */
    template <class I, unsigned int A = 1 >
    class SpecificAlgorithm_t : public GenericAlgorithm_t<typename I::depth_t, A> {
        public:
            
            /*!
             * \brief A specificaton of the function call operator used to apply the algorithm to a vector of images.
             * This method is an overload of GenericAlgorithm_t::operator(), it specify the covariant return type using the I template parameter.
             * It checks the size of the vector and return the result of the algorithm method.
             * \param imgs The vector of images on which the algorithm will be applied. The size of this vector must be equal to A.
             * \return The image resulting of the application of the algorithm.
             * \throw NotEnoughImageException if the size of the vector imgs in not equal to the Arity of the algorithm. 
             * \throw ImageTypeException if implemented in algorithm
             * \throw ImageSizeException if implemented in algorithm
             */
            inline I* operator() (const std::vector<const Image_t<typename I::depth_t>*>& imgs); 
        
        protected:
            /*!
             * \brief A specification of the concrete implementation of the algorithm
             * This method is an overload of GenericAlgorithm_t::algorithm, it specify the covariant return type using the I template parameter.
             * \param imgs The vector of images on which the algorithm will be applied. The size of this vector must be equal to A.
             * \return The image resulting of the application of the algorithm.
             * \throw ImageTypeException if implemented
             * \throw ImageSizeException if implemented
             */
            virtual I* algorithm(const std::vector<const Image_t<typename I::depth_t>*>& imgs) = 0;
    };

    #include "SpecificAlgorithm.tpp"
}

#endif //!SPECIFICALGORITHM_H
