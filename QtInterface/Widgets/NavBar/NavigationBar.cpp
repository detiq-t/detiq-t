#include "NavigationBar.h"

NavigationBar::NavigationBar() : QListView()
{
  ImageDelegate* im = new ImageDelegate;
  setItemDelegate(im);
  setFixedWidth(80);
}
