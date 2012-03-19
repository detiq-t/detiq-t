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
    template < typename D, template <typename D> class I, unsigned int A = 1 >
    class Algorithm_t : public SpecificAlgorithm_t<D, I, A> {
        
    };
    
    /*!
     * \brief A specialization of Algorithm_t with a more suitable interface
     */
    template <typename D, template <typename D> class I>
    class Algorithm_t<D,I,1> : public SpecificAlgorithm_t<D,I,1> {
        public:
        /*!
         * \brief A second overload of the function call operator to suit the arity of the algorithm
         * This method build a vector with its parameters and call the algorithm method with it.
         * \param img The image on which the algorithm will be applied.
         * \return The image resulting of the application of the algorithm.
         * \throw ImageTypeException if implemented in algorithm
         * \throw ImageSizeException if implemented in algorithm
         */
        inline I<D>* operator() (const Image_t<D>* img) const;
    };

    /*!
     * \brief A specialization of Algorithm_t with a more suitable interface
     */
    template <typename D, template <typename D> class I>
    class Algorithm_t<D,I,2> : public SpecificAlgorithm_t<D,I,2> {
        public:
        /*!
         * \brief A second overload of the function call operator to suit the arity of the algorithm
         * This method build a vector with its parameters and call the algorithm method with it.
         * \param img,img2 The images on which the algorithm will be applied.
         * \return The image resulting of the application of the algorithm.
         * \throw ImageTypeException if implemented in algorithm
         * \throw ImageSizeException if implemented in algorithm
         */
        inline I<D>* operator() (const Image_t<D>* img, const Image_t<D>* img2) const; 
    };

    /*!
     * \brief A specialization of Algorithm_t with a more suitable interface
     */
    template <typename D, template <typename D> class I>
    class Algorithm_t<D,I,3> : public SpecificAlgorithm_t<D,I,3> {
        public:
        /*!
         * \brief A second overload of the function call operator to suit the arity of the algorithm
         * This method build a vector with its parameters and call the algorithm method with it.
         * \param img,img2,img3 The images on which the algorithm will be applied.
         * \return The image resulting of the application of the algorithm.
         * \throw ImageTypeException if implemented in algorithm
         * \throw ImageSizeException if implemented in algorithm
         */
        inline I<D>* operator() (const Image_t<D>* img, const Image_t<D>* img2, const Image_t<D>* img3) const; 
    };

    /*!
     * \brief Algorithm_8<I,A> is nothing else than an Algorithm_<uint8_t, I A>
     */
    template <template <typename D> class I, unsigned int A=1 >
    class Algorithm_8 : public Algorithm_t<uint8_t, I, A> {};

    /*!
     * \brief Algorithm_16<I,A> is nothing else than an Algorithm_<uint16_t, I A>
     */
    template <template <typename D> class I, unsigned int A=1 >
    class Algorithm_16 : public Algorithm_t<uint16_t, I, A> {};

    /*!
     * \brief Algorithm_32<I,A> is nothing else than an Algorithm_<uint32_t, I A>
     */
    template <template <typename D> class I, unsigned int A=1 >
    class Algorithm_32 : public Algorithm_t<uint32_t, I, A> {};

    #include "Algorithm.tpp"
}

#endif //!ALGORITHM_H
