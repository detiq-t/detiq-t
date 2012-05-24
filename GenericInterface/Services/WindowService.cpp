#include "WindowService.h"

#include <QListIterator>

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
    QObject::connect(_nav, SIGNAL(removePath(const QString&)), this, SLOT(removePath(const QString&)));

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

        SubWindowController* swc = new SubWindowController(path, sw);
        QObject::connect(sw, SIGNAL(destroyed()), swc, SLOT(closeSubWindow()));
        QObject::connect(swc, SIGNAL(removeFromWindowsMap(const QString&, QMdiSubWindow*)),
                         this, SLOT(removeSubWindow(const QString&,QMdiSubWindow*)));

        w->show();

        _nav->addImage(path);
    }
}

void WindowService::addWidget(const QString& path, ImageWindow* widget)
{
    if(_windows.find(path) != _windows.end())
    {
        QMdiSubWindow* sw = _mdi->addSubWindow(widget);

        _windows[path] << sw;

        SubWindowController* swc = new SubWindowController(path, sw);

        QObject::connect(sw, SIGNAL(destroyed()), swc, SLOT(closeSubWindow()));
        QObject::connect(swc, SIGNAL(removeFromWindowsMap(const QString&, QMdiSubWindow*)), this, SLOT(removeSubWindow(const QString&,QMdiSubWindow*)));



        /* //TODO La mise à jour du rectangle est foireuse : cela n'agit que sur la première Image. Si elle est supprimée et qu'un Widget autre prend
                    la première place dans la liste, ça crash l'appli ! (pas de slot...)
        QMdiSubWindow* source = _windows[path][0];
        if(source != sw)
        {
            QObject::connect(widget, SIGNAL(highlightRectChange(const imagein::Rectangle*, ImageWindow*)), dynamic_cast<StandardImageWindow*>(source->widget()), SLOT(showHighlightRect(const imagein::Rectangle*, ImageWindow*)));
            QObject::connect(sw, SIGNAL(aboutToActivate()), widget, SLOT(activated()));
        }
        */
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

    if (_windows[path].empty()) removePath(path);
    //this->updateDisplay();
}

void WindowService::removePath(const QString& path)
{
    QList<QMdiSubWindow*> l = _windows[path];
    QList<QMdiSubWindow*>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
    {
        delete *it;
    }
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






SubWindowController::SubWindowController(const QString& path, QMdiSubWindow* sw) : _path(path), _sw(sw)
{
} 

void SubWindowController::closeSubWindow()
{
    emit removeFromWindowsMap(_path, _sw);
    delete this;
}
