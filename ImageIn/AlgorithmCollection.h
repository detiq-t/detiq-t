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

#ifndef ALGORITHMCOLLECTION_H
#define ALGORITHMCOLLECTION_H

#include <vector>

#include "Image.h"
#include "GenericAlgorithm.h"
#include "Algorithm.h"
#include "AlgorithmException.h"

namespace imagein
{
    /*!
     * \brief AlgorithmCollection is an algorithm made of several GenericAlgorithms
     *
     * \tparam D A typename corresponding to the Depth template parameter of the classe Image_t.
     * \tparam A An unsigned integer corresponding to the Arity of the algorithm, i.e. the number of images the algorithm takes as parameters
     * 
     * An AlgorithmCollection is created with one first algorithm called the top algorithm.
     * One can then add other algorithms which will stack themselves up under the top algorithm.
     * When the AlgorithmCollection is called with some parameters it will first call the top algorithm with it, 
     * then call the first nested algorithm with the result of the top algorithm and so on.
     * The result of the last nested algorithm will be returned.
     */
    template <typename D, unsigned int A>
    class AlgorithmCollection : GenericAlgorithm_t<D, A> {
        public:

          /*!
           * \brief The constructor wich take the top algorithm of the collection as a parameter.
           * \param algo This algorithm will always be the first algorithm to be called, it must have the same arity of the AlgorithmCollection.
           */
            AlgorithmCollection(const GenericAlgorithm_t<D, A>& algo) : _topAlgorithm(algo) {
            }

          /*!
           * \brief This method add an algorithm to the collection
           * \param algo This algorithm will added to the nested algorithms vector.
           * When the AlgorithmCollection is called, the nested algorithm are called in a FIFO order.
           */
            void Add(const GenericAlgorithm_t<D, 1>& algo) {
                _nestedAlgorithms.push_back(algo);
            }

          /*!
           * \brief Function call operator used to apply the algorithm to a vector of images.
           * This method will start by calling the top algorithm on the images parameter.
           * It will then call all the nested algorithm in a FIFO order.
           * Finally it will return the resulting image of the last called algorithm.
           * \param imgs The vector of images on which the algorithm will be applied. The size of this vector must be equal to A.
           * \return The image resulting of the succession of application of all the algorithms in the collection.
           * \throw NotEnoughImageException if the size of the vector imgs in not equal to the Arity of the top algorithm. 
           * \throw ImageTypeException if implemented in one of the algorithms of the collection
           * \throw ImageSizeException if implemented in one of the algorithms of the collection
           */
            Image_t<D>* operator()(const std::vector<Image_t<D>*>& imgs) {
                Image_t<D>* lastImage = _topAlgorithm(imgs);
                for(typename std::vector<GenericAlgorithm_t<D> >::iterator it = _nestedAlgorithms.begin()+1; it < _nestedAlgorithms.end(); ++it) {
                    lastImage = (*it)(lastImage);
                }
                return lastImage;
            }

            inline Image_t<D>* operator() (const Image_t<D>* img) { std::vector<const Image_t<D>*> imgs; imgs.push_back(img); (*this)(imgs); }

        private:
            std::vector<GenericAlgorithm_t<D, 1> > _nestedAlgorithms;
            GenericAlgorithm_t<D, A> _topAlgorithm;
    };
}

#endif //!ALGORITHMCOLLECTION_H
