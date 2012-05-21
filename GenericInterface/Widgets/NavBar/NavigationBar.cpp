#include "NavigationBar.h"

using namespace genericinterface;

NavigationBar::NavigationBar() : QListView()
{
  ImageDelegate* im = new ImageDelegate;
  setItemDelegate(im);
  setFixedWidth(80);
  setEditTriggers(QAbstractItemView::NoEditTriggers);
}
