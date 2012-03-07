#ifndef WIDGET_IMAGEVIEWER_H
#define WIDGET_IMAGEVIEWER_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QMouseEvent>

#include <iostream>
#include <cmath>

namespace genericinterface
{
  class ImageViewer : public QGraphicsView
  {
  public:
    ImageViewer (const QString & path, int x, int y);

  private:
    void init (const QString & path, int x, int y);
    void mousePressEvent(QMouseEvent * event);

    void updatePos (int x, int y);

    QGraphicsScene* _scene;
    QGraphicsRectItem* _rect;

    static const int WIDGET_S = 200;
    static const int RECT_W = 40;
    static const int RECT_H = 40;

    double _scale;
    int _supx;
    int _supy;
    int _dx;
    int _dy;
    int _ox;
    int _oy;
  };
}

#endif
