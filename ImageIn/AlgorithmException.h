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

#ifndef ALGORITHMEXCEPTION_H
#define ALGORITHMEXCEPTION_H

#include <iostream>
#include <sstream>
#include <exception>

namespace imagein
{
  //! This is the exception thrown by ImageFile and its subclasses when there is an error reading from or writing in a file.
  /*!
   * \brief AlgorithmException is a base classes for all the Exceptions thrown by the algorithms
   * Some of them are thrown directly by the abstract classes such as Algorithm_t or PixelAlgorithm_t, others is supposes to be thrown in the implementation of the algorithms.
   */
  class AlgorithmException : public std::exception
  {
    public:
        AlgorithmException(int line, std::string file)
        {
            std::ostringstream oss;
            oss << "Exception raised line " << line << " in file " << file << " : "
                << _msg;
            this->_msg = oss.str();
        }

        virtual ~AlgorithmException() throw()
        {

        }

        virtual const char * what() const throw()
        {
            return this->_msg.c_str();
        }

    private:
        std::string _msg;
  };

  /*!
   * \brief An exception thrown when an algorithm is called without enough parameters. 
   */
	class NotEnoughImageException : AlgorithmException {
    public:
        NotEnoughImageException(int line = __LINE__, std::string file = __FILE__) : AlgorithmException(line, file) {}
	};

  /*!
   * \brief An exception thrown when an algorithm is called with a wrong type of Image as a parameter. 
   */
	class ImageTypeException : AlgorithmException {
    public:
        ImageTypeException(int line, std::string file) : AlgorithmException(line, file) {}
	};

  /*!
   * \brief An exception thrown when an algorithm is called with images parameters of invalid size.
   * For instance, PixelAlgorithmi_t throws this exception when the input images are not all the same size.
   */
	class ImageSizeException : AlgorithmException {
    public:
        ImageSizeException(int line, std::string file) : AlgorithmException(line, file) {}
	};
}

#endif // ALGORITHMEXCEPTION_H
