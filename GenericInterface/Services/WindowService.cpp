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
    QObject::connect(_nav, SIGNAL(removeId(const QString&)), this, SLOT(removeId(const QString&)));

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

QString WindowService::getWidgetId(QWidget* widget)
{
    for(WidgetsMap::iterator it = _widgets.begin() ; it != _widgets.end() ; ++it)
    {
        for(int i = 0 ; i < it->second.size() ; ++i)
        {
            if(it->second.at(i)->widget() == widget) return it->first;
        }
    }
    return "";
}

void WindowService::addFile(const QString& path)
{
    if(_widgets.find(path) == _widgets.end())
    {
        StandardImageWindow* w = new StandardImageWindow(path, _gi);
        _widgets[path] = QList<QMdiSubWindow*>();
        this->addImage(path, w);
        _nav->addImage(path);
    }
}

void WindowService::addImage(const QString& id, ImageWindow* image)
{
    if(_widgets.find(id) != _widgets.end())
    {
        QMdiSubWindow* sw = _mdi->addSubWindow(image);
        _widgets[id] << sw;

        SubWindowController* swc = new SubWindowController(id, sw);

        QObject::connect(sw, SIGNAL(aboutToActivate()), image, SLOT(activated()));

        QObject::connect(sw, SIGNAL(destroyed()), swc, SLOT(closeSubWindow()));
        QObject::connect(swc, SIGNAL(removeFromWindowsMap(const QString&, QMdiSubWindow*)), this, SLOT(removeSubWindow(const QString&,QMdiSubWindow*)));

        sw->show();
    }
}

void WindowService::addWidget(const QString& id, QWidget* widget)
{
    if(_widgets.find(id) != _widgets.end())
    {
        QMdiSubWindow* sw = _mdi->addSubWindow(widget);
        _widgets[id] << sw;

        SubWindowController* swc = new SubWindowController(id, sw);

        QObject::connect(sw, SIGNAL(destroyed()), swc, SLOT(closeSubWindow()));
        QObject::connect(swc, SIGNAL(removeFromWindowsMap(const QString&, QMdiSubWindow*)), this, SLOT(removeSubWindow(const QString&,QMdiSubWindow*)));

        sw->show();
    }
}

void WindowService::removeSubWindow(const QString& id, QMdiSubWindow* sw)
{
    int i;
    bool subWindowFound = false;
    for (i=0; i<_widgets[id].size() && !subWindowFound; i++)
    {
        if (_widgets[id][i] == sw)
        {
            subWindowFound = true;
        }
    }
    _widgets[id].removeAt(i-1);

    if (_widgets[id].empty()) removeId(id);
    //this->updateDisplay();
}

void WindowService::removeId(const QString& id)
{
    QList<QMdiSubWindow*> l = _widgets[id];
    QList<QMdiSubWindow*>::iterator it;
    for (it = l.begin(); it != l.end(); it++)
    {
        delete *it;
    }
    _widgets.erase(id);
    _nav->removeImage(id);
    //this->updateDisplay();
}

void WindowService::updateDisplay()
{
    for(WidgetsMap::iterator it = _widgets.begin(); it != _widgets.end(); ++it)
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
        for(int x = 0; x < _widgets[sel[u]].size(); x++)
        {
            //_widgets[sel[u]][x]->show();
            _widgets[sel[u]][x]->showNormal();
        }
    }
}






SubWindowController::SubWindowController(const QString& id, QMdiSubWindow* sw) : _id(id), _sw(sw)
{
} 

void SubWindowController::closeSubWindow()
{
    emit removeFromWindowsMap(_id, _sw);
    delete this;
}
