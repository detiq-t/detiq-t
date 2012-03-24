#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>

#include "Image.h"
#include "SpecificAlgorithm.h"
#include "AlgorithmException.h"

namespace imagein
{
    /*!
     * \brief Algorithm_t is the main and most useful algorithm interface
     *
     * \tparam D A typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam I A templated class representing an Image type such as RgbImage_t. This classe will take the first template parameter D as its template parameter.
     * \tparam A An unsigned integer corresponding to the Arity of the algorithm, i.e. the number of images the algorithm takes as parameters
     *
     * Algorithm_t is nothing else than a SpecificAlgorithm_t with a more user-friendly interface
     * It uses the Arity template parameter to define a suitable overload of the application operator.
     * This specification cannot be done directly in SpecifiAlgorithm_t because of the c++93's limits in partial template specialization
     */
    template <class I, unsigned int A = 1>
    class Algorithm_t : public SpecificAlgorithm_t<I, A> {
    };
    
    /*!
     * \brief A specialization of Algorithm_t with a more suitable interface
     */
    template <class I>
    class Algorithm_t<I,1> : public SpecificAlgorithm_t<I,1> {
        public:
        /*!
         * \brief A second overload of the function call operator to suit the arity of the algorithm
         * This method build a vector with its parameters and call the algorithm method with it.
         * \param img The image on which the algorithm will be applied.
         * \return The image resulting of the application of the algorithm.
         * \throw ImageTypeException if implemented in algorithm
         * \throw ImageSizeException if implemented in algorithm
         */
        inline I* operator() (const Image_t<typename I::depth_t>* img);
    };

    /*!
     * \brief A specialization of Algorithm_t with a more suitable interface
     */
    template <class I>
    class Algorithm_t<I,2> : public SpecificAlgorithm_t<I,2> {
        public:
        /*!
         * \brief A second overload of the function call operator to suit the arity of the algorithm
         * This method build a vector with its parameters and call the algorithm method with it.
         * \param img,img2 The images on which the algorithm will be applied.
         * \return The image resulting of the application of the algorithm.
         * \throw ImageTypeException if implemented in algorithm
         * \throw ImageSizeException if implemented in algorithm
         */
        inline I* operator() (const Image_t<typename I::depth_t>* img, const Image_t<typename I::depth_t>* img2); 
    };

    /*!
     * \brief A specialization of Algorithm_t with a more suitable interface
     */
    template <class I>
    class Algorithm_t<I,3> : public SpecificAlgorithm_t<I,3> {
        public:
        /*!
         * \brief A second overload of the function call operator to suit the arity of the algorithm
         * This method build a vector with its parameters and call the algorithm method with it.
         * \param img,img2,img3 The images on which the algorithm will be applied.
         * \return The image resulting of the application of the algorithm.
         * \throw ImageTypeException if implemented in algorithm
         * \throw ImageSizeException if implemented in algorithm
         */
        inline I* operator() (const Image_t<typename I::depth_t>* img, const Image_t<typename I::depth_t>* img2, const Image_t<typename I::depth_t>* img3); 
    };

    #include "Algorithm.tpp"
}

#endif //!ALGORITHM_H
