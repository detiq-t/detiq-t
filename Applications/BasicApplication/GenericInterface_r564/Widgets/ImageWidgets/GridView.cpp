#include <QHBoxLayout>
#include <QGraphicsView>

#include "GridView.h"
#include "ImageViewer.h"
#include "ZoomViewer.h"

using namespace imagein;
using namespace genericinterface;

GridView::GridView(Image* im, const QString & path, int dx, int dy) : AlternativeImageView(im)
{
  _layout = new QHBoxLayout;
  _viewer = new ImageViewer(path, dx, dy);


  QGraphicsView* view = new QGraphicsView;
  view->setScene(_viewer);

  _layout->addWidget(view);

  ZoomViewer* zv = new ZoomViewer(im, ImageViewer::RECT_W, ImageViewer::RECT_H);
  QGraphicsView* viewz = new QGraphicsView;
  viewz->setScene(zv);
  _layout->addWidget(viewz);

  QObject::connect(_viewer, SIGNAL(positionUpdated(int, int)), zv, SLOT(draw(int, int)));

  setLayout(_layout);
}

void GridView::newDisplay(int x, int y)
{
}
