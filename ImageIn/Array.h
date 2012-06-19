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

#ifndef ARRAY_H
#define ARRAY_H

namespace imagein
{
    /*!
     * \brief Fixed-size array with easy to use access method. Used as a base for Histogram and ProjectionHistogram_t.
     *
     * This class represents a fixed-size array of integers. It can be seen as lightweight vector with fixed size, but is easier to use than C arrays, and provides stl-like iterators.
     */
    template <typename T>
    class Array
    {
        public:
            typedef T* iterator; //!< Random access iterator
            typedef const T* const_iterator; //!< Random access const iterator

            /*!
             * \brief Creates an array of the given size.
             *
             * Values are not initialized.
             */
            inline Array(int width=0) : _width(width) { _array = new T[width]; };
            inline virtual ~Array() { delete[] _array; };

            //! Returns the size of the array.
            inline unsigned int getWidth() const { return _width; };
            //! Access to the element at the given index.
            inline T operator[](unsigned int index) const { return _array[index]; };
            //! Constant access to the element at the given index.
            inline T& operator[](unsigned int index) { return _array[index]; };

            //! Returns an iterator to the first element of the array
            inline iterator begin() { return _array; };
            //! Returns a const_iterator to the first element of the array
            inline const_iterator begin() const { return _array; };
            //! Returns an iterator past then end of the array
            inline iterator end() { return _array+_width; };
            //! Returns a const_iterator past then end of the array
            inline const_iterator end() const { return _array+_width; };

        protected:
            T* _array;
            unsigned int _width;
    };
}

#endif // ARRAY_H
