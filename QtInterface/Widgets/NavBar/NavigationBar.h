#ifndef QTINTERFACE_WIDGET_NAVIGATIONBAR_H
#define QTINTERFACE_WIDGET_NAVIGATIONBAR_H

#include <QListView>

#include "ImageDelegate.h"

class NavigationBar : public QListView
{
public:
  NavigationBar() : QListView()
  {
    ImageDelegate* im = new ImageDelegate;
    setItemDelegate(im);
    setFixedWidth(80);
  }
};

#endif
