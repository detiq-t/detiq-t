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

#ifndef SERVICE_H_02022012
#define SERVICE_H_02022012

//namespace genericinterface
//{
//  class Service;
//}
namespace genericinterface
{
  class GenericInterface;
}



//#include "GenericInterface.h"
#include "ServiceExceptions.h"

namespace genericinterface
{
  /**
  * @brief Interface for the service, forcing the visitor behavior.
  */
  class Service
  {
  public:
    /**
    * @brief Just before the QMainWindow::show (), it is important to connect each
    * services to the other.
    *
    * @param gi a pointer to the generic interface which owns the service
    *
    * @throw ServiceConnexionException
    */
    virtual void connect (GenericInterface* gi) /*throw (ServiceConnexionException) */= 0;

    /**
    * @brief Many services needs a button, a menu or any thing else to know when its functions
    * are wanted, this function let the service change the generic interface in this aim.
    *
    * @param gi the generic interface to modifie.
    */
    virtual void display (GenericInterface* gi) = 0;
  };
}

#endif
