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

#ifndef QTINTERFACE_WINDOWSERVICE_H
#define QTINTERFACE_WINDOWSERVICE_H

#include <QDockWidget>
#include <QMdiSubWindow>

#include "../Widgets/ImageWidgets/StandardImageWindow.h"
#include "../Widgets/ImageWidgets/ImageWindow.h"
#include "../Widgets/NavBar/NavigationDock.h"
#include "../GenericInterface.h"

typedef std::map<QString, QList<QMdiSubWindow*> > WidgetsMap;

namespace genericinterface
{
  class WindowService : public QObject, public Service
  {
  Q_OBJECT
  public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

   /**
    * @brief Returns the current subwindow if it is an ImageWindow.
    */
    ImageWindow* getCurrentImageWindow();

	QString getWidgetId(QWidget* widget);

  public slots:
    void addFile(const QString& path);
    void addImage(const QString& id, ImageWindow* image);
    void addWidget(const QString& id, QWidget* widget);
    void updateDisplay();
    void removeId(const QString& id);

  signals:
    void subWindowActivated(QMdiSubWindow*);

  private slots:
    void removeSubWindow(const QString& id, QMdiSubWindow* sw);
	
  private:
    GenericInterface* _gi;
    QMdiArea* _mdi;
    NavigationDock* _nav;
    WidgetsMap _widgets;
  };


  class SubWindowController : public QObject
  {
      Q_OBJECT
  public:
      SubWindowController(const QString& id, QMdiSubWindow* sw);

  public slots:
      void closeSubWindow();

  signals:
      void removeFromWindowsMap(const QString& id, QMdiSubWindow* sw);

  private:
      QString _id;
      QMdiSubWindow* _sw;
  };
}

#endif
