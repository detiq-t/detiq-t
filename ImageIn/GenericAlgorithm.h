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
            typedef D depth_t;
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
            inline Image_t<D>* operator() (const std::vector<const Image_t<D>*>& imgs);
        protected:
            /*!
             * \brief The concrete implementation of the algorithm
             *
             * \param imgs The vector of images on which the algorithm will be applied. The size of this vector must be equal to A.
             * \return The image resulting of the application of the algorithm.
             * \throw ImageTypeException if implemented
             * \throw ImageSizeException if implemented
             */
            virtual Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) = 0;
    };
    
    /*!
     * \brief A specialization of GenericAlgorithm_t with a more suitable interface
     */
    template <typename D>
    class GenericAlgorithm_t<D,1> {
        public:
            typedef D depth_t;
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
            inline Image_t<D>* operator() (const std::vector<const Image_t<D>*>& imgs);
            /*!
             * \brief A second overload of the function call operator to suit the arity of the algorithm
             * This method build a vector with its parameters and call the algorithm method with it.
             * \param img The image on which the algorithm will be applied.
             * \return The image resulting of the application of the algorithm.
             * \throw ImageTypeException if implemented in algorithm
             * \throw ImageSizeException if implemented in algorithm
             */
            inline Image_t<D>* operator() (const Image_t<D>* img);
        protected:
            /*!
             * \brief The concrete implementation of the algorithm
             *
             * \param imgs The vector of images on which the algorithm will be applied. The size of this vector must be equal to A.
             * \return The image resulting of the application of the algorithm.
             * \throw ImageTypeException if implemented
             * \throw ImageSizeException if implemented
             */
            virtual Image_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs) = 0;
    };
}

#include "GenericAlgorithm.tpp"

#endif //!GENERICALGORITHM_H
