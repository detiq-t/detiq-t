#ifndef WIDGET_IMAGEVIEWER_H
#define WIDGET_IMAGEVIEWER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QString>



/**
* @brief Provides a way to display a miniature of the picture
*/
class QMouseEvent;
class QGraphicsRectItem;
class QGraphicsSceneMouseEvent;

namespace genericinterface
{
  /**
  * @brief [Inner class] This item displays the pictures in a little scale, then the
  * users it without cropping
  *
  * In Qt architecture, it's an item, it's mean it has to be used with
  * a QGraphicsScene. Thanks to sigals, it tells where the user wants the
  * picture to be zoomed.
  */
  class ImageItem : public QObject, public QGraphicsPixmapItem
  {
  Q_OBJECT
  public:
    /**
    * @brief The constructor of the controller
    *
    * @param pix A pixmap creating with the picture
    */
    ImageItem(QPixmap& pix);

    /**
    * @brief The overloading of mousePressEvent Qt's function, leading the
    * mouse events
    *
    * @param event the event in treatment
    */
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
  
  signals:
    /**
    * @brief [signal] this signal prevents listenners of the item that 
    *
    * @param x the horizontal position of the click
    * @param y the vertical position of the click
    */
    void clickListenned(int x, int y);

  private:
    bool _moving;
  };

  /**
  * @brief The ImageViewer is like a controller for the grid.
  */
  class ImageViewer : public QGraphicsScene
  {

  Q_OBJECT
  public:
    ImageViewer (const QString & path, int x, int y);

    static const int RECT_W = 30; /*!< The number of horizontal pixels in the grid */
    static const int RECT_H = 21; /*!< The number of vertical pixels in the grid */

    /**
    * @brief Getter of the horizontal offset (the top left of the grid position in the image
    *
    * @return the integer value
    */
    inline int dx() { return _dx; };
    inline int dy() { return _dy; };

    /**
    * @brief Getter of the vertical offset (the top left of the grid position in the image
    *
    * @return the integer value
    */

  public slots:
    /**
    * @brief [slots] The default behavior is to connect the clickListenned
    * signal with this slot. Thanks to that, the controller can compute
    * the exact coordinate of the click on the original (and weel-sized)
    * window
    *
    * @param x x-coordinate received
    * @param y y-coordinate received
    */
    void slotPositionReception(int x, int y);

  signals:
    /**
    * @brief [signals] Ask for a refreshment of the grid
    *
    * @param x the x's top left point of the grid
    * @param y the y's top left point of the grid
    */
    void positionUpdated(int x, int y);

  private:
    void init (const QString & path, int x, int y);

    void updatePos (int x, int y);

    QGraphicsScene* _scene;
    QGraphicsRectItem* _rect;

    static const int WIDGET_S = 200;

    double _scale; /*!< the scale between miniature and original picture */
    int _supx; /*!< the max value of _ox + _dx */
    int _supy;
    int _dx; /*!< the offset of the miniature in the scene */
    int _dy;
    int _ox; /*!< the offset of the zoomed zone in the miniature */
    int _oy;
  };
}

#endif
