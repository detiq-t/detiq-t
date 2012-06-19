/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

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
