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

#ifndef SERVICEEXCEPTIONS_H_02022012
#define SERVICEEXCEPTIONS_H_02022012

#include <sstream>
#include <exception>


namespace genericinterface
{
  /**
  * @brief One task of the Services is to connect themself,
  * with their connect() methods. If the connection is impossible,
  * the service throw a ServiceConnectionException.
  */
  class ServiceConnectionException : public std::exception
  {
    public:
      /**
      * @brief The constructor of a ServiceConnectionException
      *
      * @param src The id of the service which asks a connection
      * @param dst The id of the target service
      */
      ServiceConnectionException(int src, int dst)
      {
        _src = src;
        _dst = dst;
      }

      virtual const char* what () const throw ()
      {
        std::ostringstream err;
        err << "the service " << _src << " fails to connect with the service " << _dst;
        err << ", check the ids";

        return err.str ().c_str ();
      }
    private:
      int _src; /*!< The id of the service which asks a connection */
      int _dst; /*!< The id of the target service */
  };
}

#endif
