#ifndef QTINTERFACE_WIDGET_NAVIGATIONDOCK
#define QTINTERFACE_WIDGET_NAVIGATIONDOCK

#include <iostream>

#include <QHBoxLayout>

#include <QStringListModel>
#include <QMenu>
#include <QAction>

#include "NavigationBar.h"

class NavigationDock : public QWidget
{
Q_OBJECT
public:
  /**
  * @brief Default constructor, layout the elements
  */
  NavigationDock();

public slots:
  /**
  * @brief 
  *
  * @param path
  */
  void addImage(const QString& path);

protected slots:
  /**
  * @brief 
  *
  * @param pos
  */
  void showContextMenu(const QPoint& pos);

signals:

private:
  QStringList _data;
  QStringListModel* _model;
  NavigationBar* _view;
  QMenu* _contextMenu;

};

#endif
