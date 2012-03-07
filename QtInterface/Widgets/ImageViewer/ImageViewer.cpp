#include "ImageViewer.h"

using namespace genericinterface;
using namespace std;

ImageViewer::ImageViewer (const QString & path, int x, int y) : QGraphicsView ()
{
  setFixedWidth(WIDGET_S + 10);
  setFixedHeight(WIDGET_S + 10);

  init(path, x, y);

  setScene (_scene);
}

void ImageViewer::init(const QString & path, int x, int y)
{
  /* Get info about the image */
  QSize size = (QImage(path)).size();

  int height = size.height();
  int width = size.width();
  int sup = max(height, width);

  /* Compute the numeric attributs of our object */
  _scale = sup > WIDGET_S ? (double) WIDGET_S / (double) sup : 1.0;

  _dx = (WIDGET_S - width * _scale) / 2;
  _dy = (WIDGET_S - height * _scale) / 2;

  _supx = width * _scale;
  _supy = height * _scale;

  cout << _supx << ":" << _supy << endl;



  /* Creats the scene */
  _scene = new QGraphicsScene (0, 0, 200, 200);

  QPixmap i(path);
  i = i.scaled(width * _scale, height * _scale);

  QGraphicsPixmapItem* im = new QGraphicsPixmapItem(i);
  im->setOffset(_dx, _dy);

  _scene->addItem(im);
  _rect = new QGraphicsRectItem(0, 0, _scale * 40, _scale * 30);

  QPen b;
  b.setColor(Qt::red);

  _rect->setPen(b);

  _scene->addItem(_rect);

  updatePos(x * _scale, y * _scale);
}

void ImageViewer::updatePos (int x, int y)
{
  _ox = x - RECT_W * _scale / 2;
  _ox = min(_ox, _supx - RECT_W / 2);
  _ox = max(_ox, 0);

  _oy = y - RECT_H * _scale / 2;
  _oy = min(_oy, _supy - RECT_H / 2);
  _oy = max(_oy, 0);

  cout << "\t" << _ox << ";" << _oy << endl;

  _rect->setX(_dx + _ox);
  _rect->setY(_dy + _oy);
}

void ImageViewer::mousePressEvent(QMouseEvent * event)
{
  int x = event->x() - _dx;
  int y = event->y() - _dy;


  updatePos(x, y);
}

