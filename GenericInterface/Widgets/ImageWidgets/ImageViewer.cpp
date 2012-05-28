#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <cmath>
#include <iostream>
#include <QGraphicsSceneMouseEvent>

#include "ImageViewer.h"

using namespace genericinterface;
using namespace std;

ImageItem::ImageItem(QPixmap& pix) : QGraphicsPixmapItem(pix), _moving(false) { }

void ImageItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  _moving = true;
}

void ImageItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  _moving = false;
}

void ImageItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if(_moving) {
    int x = event->pos().x();
    int y = event->pos().y();

    emit clickListenned(x, y);
  }
}

ImageViewer::ImageViewer (const imagein::Image* img, int x, int y) : QGraphicsScene (0, 0, WIDGET_S, WIDGET_S)
{
  init(img, x, y);
}

void ImageViewer::init(const imagein::Image* img, int x, int y)
{
  /* Get info about the image */
  QImage qimg = getQImage(img);
  QSize size = (qimg).size();

  int height = size.height();
  int width = size.width();
  int sup = max(height, width);

  /* Compute the numeric attributs of our object */
  _scale = sup > WIDGET_S ? (double) WIDGET_S / (double) sup : 1.0;

  _dx = (WIDGET_S - width * _scale) / 2;
  _dy = (WIDGET_S - height * _scale) / 2;

  _supx = width * _scale;
  _supy = height * _scale;


  /* Creats the scene */

  QPixmap i;
  i.convertFromImage(qimg);
  i = i.scaled(width * _scale, height * _scale);

  //QGraphicsPixmapItem* im = new QGraphicsPixmapItem(i);
  ImageItem* im = new ImageItem(i);
  im->setOffset(_dx, _dy);

  QObject::connect(im, SIGNAL(clickListenned(int, int)), this, SLOT(slotPositionReception(int, int)));

  addItem(im);
  _rect = new QGraphicsRectItem(0, 0, _scale * RECT_W, _scale * RECT_H);

  QPen b;
  b.setColor(Qt::red);

  _rect->setPen(b);

  addItem(_rect);
  _rect->setX(_dx);
  _rect->setY(_dy);

  updatePos(x * _scale, y * _scale);
}

void ImageViewer::updatePos (int x, int y)
{
  _ox = x - RECT_W * _scale / 2 - _dx;
  _ox = min(_ox, 0 + _supx - static_cast<int>(RECT_W * _scale));
  _ox = max(_ox, 0);

  _oy = y - RECT_H * _scale / 2 - _dy;
  _oy = min(_oy, _supy - static_cast<int>(RECT_H * _scale));
  _oy = max(_oy, 0);

  _rect->setX(_dx + _ox);
  _rect->setY(_dy + _oy);
}

void ImageViewer::slotPositionReception(int x, int y)
{
  updatePos(x, y);

  emit positionUpdated (_ox / _scale, _oy / _scale);
}

