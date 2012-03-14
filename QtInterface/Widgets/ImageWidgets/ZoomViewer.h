#ifndef WIDGET_ZOOMVIEWER_H
#define WIDGET_ZOOMVIEWER_H

#include <QObject>
#include <QGraphicsScene>
#include <Image.h>

class QGraphicsRectItem;
class QGraphicsTextItem;

namespace genericinterface
{
  class ZoomViewer : public QGraphicsScene
  {
  Q_OBJECT
  public:
    ZoomViewer(imagein::Image* im, int row, int col);

  public slots:
    void draw(int x, int y);

  private:
    QGraphicsRectItem& at(int i, int j);
    QGraphicsTextItem& atText(int i, int j);

    static const int PIXEL_S = 25;

    imagein::Image* _image;
    int _row;
    int _col;
    QGraphicsRectItem* _rects;
    QGraphicsTextItem* _texts;
  };
}

#endif
