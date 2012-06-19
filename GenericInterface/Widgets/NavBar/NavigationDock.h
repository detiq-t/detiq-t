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

#ifndef QTINTERFACE_WIDGET_NAVIGATIONDOCK
#define QTINTERFACE_WIDGET_NAVIGATIONDOCK

#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringListModel>
#include <QMenu>
#include <QModelIndex>
#include <QAction>

#include "NavigationBar.h"

namespace genericinterface
{
class NavigationDock : public QWidget
{
    Q_OBJECT
public:
    /**
    * @brief Default constructor, layout the elements
    */
    NavigationDock();

    QStringList getSelection();

public slots:
    /**
    * @brief
    *
    * @param path
    */
    void addImage(const QString& path);
    void removeImage(const QString& path);

protected slots:
    /**
    * @brief
    *
    * @param pos
    */
    void showContextMenu(const QPoint& pos);
    void emitAction(const QModelIndex& index);
    void closeSelection();

signals:
    void actionDone();
    void removeId(const QString& path);

private:
    QStringList _data;
    QStringListModel* _model;
    NavigationBar* _view;
    QMenu* _contextMenu;

};
}

#endif
