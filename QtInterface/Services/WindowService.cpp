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
}

void WindowService::addFile(const QString& path)
{
  std::cout << path.toStdString() << std::endl;
  Image* image = new Image(path.toStdString());
  genericinterface::StandardImageWindow* w = new genericinterface::StandardImageWindow(_mdi, image);
  _mdi->addSubWindow(w);
  w->show();
  
  _nav->addImage(path);
}
