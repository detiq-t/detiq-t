#ifndef WIDGET_GRIDWINDOW_H
#define WIDGET_GRIDWINDOW_H

#include "../ImageWidgets/ImageWindow.h"

namespace genericinterface
{
  class GridView;

  class GridWindow : public ImageWindow
  {
  public:
    GridWindow(const QString & path, ImageWindow* source = 0, imagein::Rectangle* rect = 0);

  protected:
    GridView* _view;
  };
}

#endif
