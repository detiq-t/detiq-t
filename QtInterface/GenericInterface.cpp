#include "GenericInterface.h"

using namespace std;

GenericInterface::GenericInterface()
{
  addService(0, new WindowService);
  addService(1, new FileService);
}

void GenericInterface::addService(int id, Service* s) throw (BadIdException)
{
  if (_services.find(id) == _services.end())
  {
    _services[id] = s;
  }
  else
    throw new BadIdException(id);
}

void GenericInterface::changeService(int id, Service* s) throw (BadIdException)
{
  if (_services.find(id) == _services.end())
    throw new BadIdException(id);
  else
  {
   delete _services[id];
    _services[id] = s;
  }
}

Service* GenericInterface::getService(int id) throw (BadIdException)
{
  if (_services.find(id) == _services.end())
    throw new BadIdException(id);
  else
    return _services[id];
}


void GenericInterface::run(bool shw)
{
  bool fail(false);

  for (map<int, Service*>::iterator it = _services.begin() ; it != _services.end() ; ++it)
  {
    try
    {
      (*it).second->display(this);
    }
    catch (ServiceConnectionException e)
    {
      Log::info(e.what());
      fail = true;
    }
  }
  for (map<int, Service*>::iterator it = _services.begin() ; it != _services.end() ; ++it)
  {
    try
    {
      (*it).second->connect(this);
    }
    catch (ServiceConnectionException e)
    {
      Log::info(e.what());
      fail = true;
    }
  }

  if (fail)
  {
    QMessageBox::critical(this, "Intégrité de la fenêtre", "La construction de l'application ne s'est pas "
                                                            "déroulée correctement, il est possible qu'elle "
                                                            "ne présente pas toutes les fonctionnalités "
                                                            "attendues");
  }

  if (shw) this->show();
}

QMdiArea* GenericInterface::initCentralWidget()
{
  static bool init(false);
  QMdiArea* res;

  if (!init)
  {
    init = true;
    res = new QMdiArea;
    setCentralWidget(res);
  }
  else
    throw new AlreadyInitException;

  return res;
}

QMenu* GenericInterface::menu(QString name)
{
  QMenu* res;

  if (_menus.find(name) != _menus.end())
  {
    res = _menus[name];
  }
  else
  {
    res = menuBar()->addMenu(name);
    _menus[name] = res;
  }

  return res;
}
