#include "GenericInterface.h"

using namespace std;

void GenericInterface::addService (int id, Service* s) throw (BadIdException)
{
}

void GenericInterface::changeService (int id, Service* s)
{
}

Service* GenericInterface::service (int id)
{
  return 0;
}

void GenericInterface::run (bool shw)
{
  map<int, Service*>::iterator it = _services.begin ();
  bool fail (false);

  for (;it != _services.end (); ++it)
  {
    try
    {
      (*it).second->connect (this);
    }
    catch (ServiceConnectionException e)
    {
      Log::info (e.what ());
      fail = true;
    }
  }

  if (fail)
  {
    QMessageBox::critical (this, "Intégrité de la fenêtre", "La construction de l'application ne s'est pas "
                                                            "déroulée correctement, il est possible qu'elle "
                                                            "ne présente pas toutes les fonctionnalités "
                                                            "attendues");
  }

  if (shw) this-> show ();
}
