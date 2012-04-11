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
