#include "GenericInterface.h"

using namespace std;

void GenericInterface::addService (int id, Service* s) throw (BadIdException)
{
  if (_services.find(id) == _services.end())
  {
    _services[id] = s;
    s->display(this);
  }
  else
    throw new BadIdException(id);
}

void GenericInterface::changeService (int id, Service* s)
{
  // delete s
}

Service* GenericInterface::service (int id)
{
  return 0;
}

void GenericInterface::run (bool shw)
{
  bool fail (false);

  for (map<int, Service*>::iterator it = _services.begin () ; it != _services.end () ; ++it)
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

QMdiArea* GenericInterface::initCentralWidget ()
{
  static bool init (false);
  QMdiArea* res;

  if(!init)
  {
    init = true;
    res = new QMdiArea;
    setCentralWidget (res);
  }
  else
    throw new AlreadyInitException;

  return res;
}

QMenu* GenericInterface::menu(QString name)
{
  QMenu* res;

  if (_menus.find (name) != _menus.end ())
  {
    res = _menus[name];
  }
  else
  {
    res = menuBar ()->addMenu (name);
    _menus[name] = res;
  }

  return res;
}
