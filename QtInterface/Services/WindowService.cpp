#include "WindowService.h"

using namespace genericinterface;


void WindowService::connect (GenericInterface* gi)
{
  _gi = gi;
}

void WindowService::display (GenericInterface* gi)
{
  _mdi = gi->initCentralWidget();

  QDockWidget* dock = new QDockWidget("Barre de navigation", gi);
  gi->addDockWidget(Qt::LeftDockWidgetArea, dock);

  dock->setWidget(_nav = new NavigationDock);
  QObject::connect(_nav, SIGNAL(actionDone()), this, SLOT(updateDisplay()));
}

void WindowService::addFile(const QString& path)
{
  if(_windows.find(path) == _windows.end())
  {
    genericinterface::StandardImageWindow* w = new genericinterface::StandardImageWindow(path, _gi);
    //_windows[path] << _mdi->addSubWindow(w);
	 QMdiSubWindow* sw = _mdi->addSubWindow(w);
	 _windows[path] << sw;
	 SubWindowController* swc = new SubWindowController(path, sw);
	 QObject::connect(sw, SIGNAL(destroyed()), swc, SLOT(closeSubWindow()));
	 QObject::connect(swc, SIGNAL(removeFromWindowsMap(const QString&, QMdiSubWindow*)), this, SLOT(removeSubWindow(const QString&,QMdiSubWindow*)));

    w->show();

    _nav->addImage(path);
  }
}

void WindowService::addWidget(const QString & path, QWidget* widget)
{
  if(_windows.find(path) != _windows.end())
  {
    QMdiSubWindow* sw = _mdi->addSubWindow(widget);

    _windows[path] << sw;

    SubWindowController* swc = new SubWindowController(path, sw);

    QObject::connect(sw, SIGNAL(destroyed()), swc, SLOT(closeSubWindow()));
    QObject::connect(swc, SIGNAL(removeFromWindowsMap(const QString&, QMdiSubWindow*)), this, SLOT(removeSubWindow(const QString&,QMdiSubWindow*)));

    widget->show();
  }
}

void WindowService::removeSubWindow(const QString& path, QMdiSubWindow* sw)
{
  int i;
  for(i=0; i<_windows[path].size(); i++)
  {
    if (_windows[path][i] == sw)
	 {
	   break;
	 }
  }
  _windows[path].removeAt(i);
  //TODO Détruire à ce moment le controller associé ?
}

void WindowService::updateDisplay()
{
  for(WindowsMap::iterator it = _windows.begin(); it != _windows.end(); ++it)
  {
    QList<QMdiSubWindow*> list = (*it).second;

    for(int u = 0; u < list.size(); u++)
    {
      list[u]->hide();
    }
  }

  QStringList sel = _nav->getSelection();

  for(int u = 0; u < sel.size(); u++)
  {
    for(int x = 0; x < _windows[sel[u]].size(); x++)
    {
      _windows[sel[u]][x]->show();
    }
  }
}







SubWindowController::SubWindowController(const QString& path, QMdiSubWindow* sw) : _path(path), _sw(sw)
{} 



void SubWindowController::closeSubWindow()
{
  emit removeFromWindowsMap(_path, _sw);
}
