#include "WindowService.h"

using namespace genericinterface;
using namespace imagein;

void WindowService::display(GenericInterface* gi)
{
  _mdi = gi->initCentralWidget();

  QDockWidget* dock = new QDockWidget(gi);
  gi->addDockWidget(Qt::LeftDockWidgetArea, dock);

  dock->setWidget(_nav = new NavigationDock);
}

void WindowService::connect(GenericInterface* gi)
{
  _gi = gi;
  QObject::connect(_nav, SIGNAL(actionDone()), this, SLOT(updateDisplay()));
  QObject::connect(_nav, SIGNAL(removeRootImage(const QString&)), this, SLOT(removeRootImage(const QString&)));
  
  QObject::connect(_mdi, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SIGNAL(subWindowActivated(QMdiSubWindow*)));
}

ImageWindow* WindowService::getCurrentImageWindow()
{
  QMdiSubWindow* sw = _mdi->currentSubWindow();
  
  if(sw != NULL) {
      ImageWindow* imw = dynamic_cast<ImageWindow*>(sw->widget());
        return imw;
  }
  else return NULL;
}

void WindowService::addFile(const QString& path)
{
  if(_windows.find(path) == _windows.end())
  {
    StandardImageWindow* w = new StandardImageWindow(path, _gi);
    QMdiSubWindow* sw = _mdi->addSubWindow(w);
    _windows[path] << sw;
    SubWindowController* swc = new SubWindowController(path, sw, true);
    QObject::connect(sw, SIGNAL(destroyed()), swc, SLOT(closeSubWindow()));
    QObject::connect(swc, SIGNAL(removeFromWindowsMap(const QString&, QMdiSubWindow*)), this, SLOT(removeSubWindow(const QString&,QMdiSubWindow*)));
    QObject::connect(swc, SIGNAL(removeFromWindowsMapAllPath(const QString&)), this, SLOT(removePath(const QString&)));

    w->show();

    _nav->addImage(path);
  }
}

void WindowService::addWidget(const QString & path, ImageWindow* widget)
{
  if(_windows.find(path) != _windows.end())
  {
    QMdiSubWindow* sw = _mdi->addSubWindow(widget);

    _windows[path] << sw;

    SubWindowController* swc = new SubWindowController(path, sw, false);

    QObject::connect(sw, SIGNAL(destroyed()), swc, SLOT(closeSubWindow()));
    QObject::connect(swc, SIGNAL(removeFromWindowsMap(const QString&, QMdiSubWindow*)), this, SLOT(removeSubWindow(const QString&,QMdiSubWindow*)));

    QMdiSubWindow* source = _windows[path][0];

    if(source != sw)
    {
      QObject::connect(widget, SIGNAL(highlightRectChange(const imagein::Rectangle*, ImageWindow*)), dynamic_cast<StandardImageWindow*>(source->widget()), SLOT(showHighlightRect(const imagein::Rectangle*, ImageWindow*)));
      QObject::connect(sw, SIGNAL(aboutToActivate()), widget, SLOT(activated()));
    }
    widget->show();
  }
}

void WindowService::addWidget(const QString& path, QWidget* widget)
{
  QMdiSubWindow* sw = _mdi->addSubWindow(widget);
  _windows[path] << sw;
  widget->show();
}
 
void WindowService::removeSubWindow(const QString& path, QMdiSubWindow* sw)
{
  int i;
  bool subWindowFound = false;
  for (i=0; i<_windows[path].size() && !subWindowFound; i++)
  {
    if (_windows[path][i] == sw)
    {
      subWindowFound = true;
    }
  }
  _windows[path].removeAt(i-1);
  //this->updateDisplay();
}

void WindowService::removePath(const QString& path)
{
  for(int i=1; i<_windows[path].size(); i++)
  {
    //_windows[path][i]->close();
	 delete _windows[path][i];
  }
  _windows[path].removeAt(0); // The first element of the list is necessary the root image
  _windows.erase(path);
  _nav->removeImage(path);
  //this->updateDisplay();
}

void WindowService::updateDisplay()
{
  for(WindowsMap::iterator it = _windows.begin(); it != _windows.end(); ++it)
  {
    QList<QMdiSubWindow*> list = (*it).second;

    for(int u = 0; u < list.size(); u++)
    {
      list[u]->showMinimized();
      //list[u]->hide();
    }
  }

  QStringList sel = _nav->getSelection();

  for(int u = 0; u < sel.size(); u++)
  {
    for(int x = 0; x < _windows[sel[u]].size(); x++)
    {
      //_windows[sel[u]][x]->show();
      _windows[sel[u]][x]->showNormal();
    }
  }
}

void WindowService::removeRootImage(const QString& path)
{
  if (_windows.find(path) != _windows.end())
    _windows[path][0]->close();
}




SubWindowController::SubWindowController(const QString& path, QMdiSubWindow* sw, bool isRootImage) : _path(path), _sw(sw)
{
  _isRootImage = isRootImage;
} 

void SubWindowController::closeSubWindow()
{
  if (_isRootImage)
  {
    emit removeFromWindowsMapAllPath(_path);
  }
  else
  {
    emit removeFromWindowsMap(_path, _sw);
  }

  delete this;
}
