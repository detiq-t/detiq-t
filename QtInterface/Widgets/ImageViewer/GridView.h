#ifndef WIDGET_ZOOMWIDGET_H
#define WIDGET_ZOOMWIDGET_H

#include <Image.h>
#include "../ImageWidgets/AlternativeImageView.h"

class QHBoxLayout;

namespace genericinterface
{
  class ImageViewer;

  class GridView : public AlternativeImageView
  {
  public:
    GridView(imagein::Image* im, const QString & path, int dx, int dy);

  public slots:
    void newDisplay(int x, int y);

  private:
    QHBoxLayout* _layout;
    ImageViewer* _viewer;
  };
}

#endif
