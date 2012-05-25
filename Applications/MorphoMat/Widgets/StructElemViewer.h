#ifndef WIDGET_STRUCTELEMVIEWER_H
#define WIDGET_STRUCTELEMVIEWER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <GrayscaleImage.h>
#include <Algorithm/MorphoMat.h>

class QGraphicsRectItem;
class QGraphicsTextItem;

/**
* @brief The grid.
*/

class StructElemViewer : public QGraphicsScene
{
    Q_OBJECT
  public:
    StructElemViewer(imagein::MorphoMat::StructElem<imagein::depth_default_t>& elem);
    ~StructElemViewer();

  public slots:
    /**
    * @brief [slot] update the grid, the new top left is (x, y)
    *
    * @param x x-coordinate of the top left
    * @param y y-coordinate of the top left
    */
    void draw(int x, int y);

  protected:
    void mousePressEvent (QGraphicsSceneMouseEvent* event);

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
    * @brief Size of one pixel (in pixel... loop !)
    */
    static const int PIXEL_S = 16;

    imagein::MorphoMat::StructElem<imagein::depth_default_t>& _image;
    unsigned int _scale;
    int _row;
    int _col;
    QGraphicsRectItem* _rects;
};

#endif
