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

#ifndef INTERFACEEXCEPTIONS_H_02022012
#define INTERFACEEXCEPTIONS_H_02022012

#include <sstream>
#include <exception>

/**
* @file InterfaceExceptions.h
* @brief Set of exceptions which can be throwed by the GenericInterface
* @author Detiq-T
* @version 0.1
* @date 2012-02-15
*/

namespace genericinterface
{

  /**
  * @brief When you add a new Service to the GenericInterface, be careful with the
  * choice of your ID, if it is already used, the Interface will throw a BadIdException
  */
  class BadIdException : public std::exception
  {
    public:
      /**
      * @brief The constructor of the exception
      *
      * @param id The id which caused the creation of the exception
      */
      BadIdException (int id)
      {
        _id = id;
      }

      /**
      * @brief Getter for the error message
      *
      * @return a simple phrase explain which id caused the error
      */
      virtual const char* what () const throw ()
      {
        std::ostringstream err;
        err << "the id " << _id << " is already used";

        return err.str ().c_str ();
      }
    private:
      /**
      * @brief The wrong id
      */
      int _id;
  };

  class AlreadyInitException : public std::exception
  {
    public:
      /**
      * @brief Getter for the error message
      *
      * @return a simple phrase explain which id caused the error
      */
      virtual const char* what () const throw ()
      {
        std::ostringstream err;
        err << "the central widget has already been initialized";

        return err.str ().c_str ();
      }
  };
}
#endif
