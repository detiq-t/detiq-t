#include "WindowService.h"


void WindowService::connect (GenericInterface* gi)
{
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
    Image* image = new Image(path.toStdString());
    genericinterface::StandardImageWindow* w = new genericinterface::StandardImageWindow(_mdi, image);
    _windows[path] << _mdi->addSubWindow(w);
    w->show();

    _nav->addImage(path);
  }
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
