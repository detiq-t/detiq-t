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

#ifndef STANDARDIMAGEVIEW_H
#define STANDARDIMAGEVIEW_H

#include <QCursor>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QString>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QKeyEvent>
#include <QObject>
#include <iostream>

#include "ImageContextMenu.h"
#include "GenericHistogramView.h"
#include "ImageWindow.h"

#include <Image.h>
#include <Rectangle.h>

namespace genericinterface
{
  QImage getQImage(const imagein::Image* image);
  /*!
   * \brief Display an image from imagein
   *
   * Display an image from imagein and manages mouse events
   */
  class StandardImageView : public QObject, public QGraphicsPixmapItem
  {
  Q_OBJECT

  public:
		/*!
		 * \brief Default constructor
		 * 
		 * Display image.
		 * 
		 * \param parent The parent widget
		 * \param image The image to display
		 */
    StandardImageView(QWidget* parent, imagein::Image* image);
        
		/*!
		 * \brief StandardImageView destructor.
		 */
		virtual ~StandardImageView();
    
    void setImage(imagein::Image* image);
    
		//! Returns the image
    inline const imagein::Image* getImage() const { return _image; }
        
		//! Returns the pixmap
    inline const QPixmap* getPixmap() const { return _pixmap_img; }
        
		//! Returns the selection rectangle
    inline imagein::Rectangle* getRectangle() const { return _selection; }
        
		//! Returns the graphics view
    inline QGraphicsView* getGraphicsView() const { return _view; }

	public slots:
    void ctrlPressed();
    void showHighlightRect(const imagein::Rectangle* rect, ImageWindow* source);
		
	signals:
		/*!
		 * \brief Signal emits when the mouse left button is clicked
		 * 
		 * \param x X coordinate of click
		 * \param y Y coordinate of click
		 */
		void pixelClicked(int x, int y) const;
		
		/*!
		 * \brief Signal emits when the mouse move over the view
		 * 
		 * \param x X coordinate of mouse
		 * \param y Y coordinate of mouse
		 */
		void pixelHovered(int x, int y) const;
		
		/*!
		 * \brief Signal emits when zoom is changed
		 * 
		 * \param z The zoom factor
		 */
		void zoomChanged(double z) const;
    
  private slots:
    void selectAll();
    
  private:
    QWidget* _parent;
    QGraphicsScene* _scene;
    QGraphicsView* _view;
    QGraphicsRectItem* _highlight;
    QPixmap* _pixmap_img;
    GenericHistogramView* _sourceHighlight;
    
    imagein::Image* _image;
    imagein::Rectangle* _selection;
    imagein::Rectangle* _visibleArea;
    ImageContextMenu* _menu;
    
    bool _ctrlPressed;
    double _zoomFactor;
    bool _mouseButtonPressed;
    QPoint* _pixelClicked;
    imagein::Rectangle* _originalHighlight;
    bool _resize;
    bool _move;
    bool _originX;
    bool _originY;
    bool _vLine;
    bool _hLine;
    
    void initMenu();
    void showImage();
    Qt::CursorShape mouseOverHighlight(int x, int y);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event);
    void wheelEvent(QGraphicsSceneWheelEvent* event);
  };
}

#endif // STANDARDIMAGEVIEW_H
