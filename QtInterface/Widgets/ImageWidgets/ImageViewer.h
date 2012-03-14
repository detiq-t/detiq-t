#ifndef WIDGET_IMAGEVIEWER_H
#define WIDGET_IMAGEVIEWER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QString>

class QMouseEvent;
class QGraphicsRectItem;
class QGraphicsSceneMouseEvent;

namespace genericinterface
{
  class ImageItem : public QObject, public QGraphicsPixmapItem
  {
  Q_OBJECT
  public:
    ImageItem(QPixmap& pix) : QGraphicsPixmapItem(pix) { }
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
  
  signals:
    void clickListenned(int x, int y);
  };

  class ImageViewer : public QGraphicsScene
  {

  Q_OBJECT
  public:
    ImageViewer (const QString & path, int x, int y);

    static const int RECT_W = 30;
    static const int RECT_H = 21;

    inline int dx() { return _dx; };
    inline int dy() { return _dy; };

  public slots:
    void slotPositionReception(int x, int y);

  signals:
    void positionUpdated(int x, int y);

  private:
    void init (const QString & path, int x, int y);

    void updatePos (int x, int y);

    QGraphicsScene* _scene;
    QGraphicsRectItem* _rect;

    static const int WIDGET_S = 200;

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
