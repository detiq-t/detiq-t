#ifndef WIDGET_ZOOMVIEWER_H
#define WIDGET_ZOOMVIEWER_H

#include <QObject>
#include <QGraphicsScene>
#include <Image.h>

class QGraphicsRectItem;
class QGraphicsTextItem;

/**
* @brief The grid.
*/

namespace genericinterface
{
  class ZoomViewer : public QGraphicsScene
  {
  Q_OBJECT
  public:
    ZoomViewer(imagein::Image* im, int row, int col);

  public slots:
    /**
    * @brief [slot] update the grid, the new top left is (x, y)
    *
    * @param x x-coordinate of the top left
    * @param y y-coordinate of the top left
    */
    void draw(int x = -1, int y = -1);

  /**
   * @brief [slot] The ZoomViewer can show the value of only one channel
   *
   * @param c the new channel to show
   */
    void channelChosen(int c);

  private:
    /**
    * @brief Get the square item representing the pixel (to changed the color, for example)
    *
    * @param i the x-coordinate
    * @param j the y-coordinate
    *
    * @return A reference to the QGraphicsRectItem
    */
    QGraphicsRectItem& at(int i, int j);

    /**
    * @brief Get the text dealing with the values of a pixel
    *
    * @param i the x-coordinate
    * @param j the y-coordinate
    *
    * @return A reference to the QGraphicsTextItem
    */
    QGraphicsTextItem& atText(int i, int j);

    /**
    * @brief Size of one pixel (in pixel... loop !)
    */
    static const int PIXEL_S = 25;

    imagein::Image* _image;
    int _row;
    int _col;
    int _channel;
    QGraphicsRectItem* _rects;
    QGraphicsTextItem* _texts;
  };
}

#endif
