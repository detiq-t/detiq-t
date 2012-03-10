#ifndef STANDARDIMAGEVIEW_H
#define STANDARDIMAGEVIEW_H

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

#include <Image.h>
#include <Rectangle.h>

using namespace imagein;

namespace genericinterface
{
    class StandardImageView : public QObject, public QGraphicsPixmapItem
    {
		Q_OBJECT
    private:
        QWidget* _parent;
		QGraphicsScene* _scene;
		QGraphicsView* _view;
		QGraphicsRectItem* _highlight;
        QPixmap* _pixmap_img;
        
        Image* _image;
        Rectangle* _selection;
        Rectangle* _visibleArea;
        ImageContextMenu* _menu;
        
        bool _ctrlPressed;
        double _zoomFactor;
        bool _mouseButtonPressed;
        QPoint* _pixelClicked;
        
        void initMenu();
        void showImage();
        void mousePressEvent(QGraphicsSceneMouseEvent * event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
        void hoverMoveEvent(QGraphicsSceneHoverEvent* event);
        void wheelEvent(QGraphicsSceneWheelEvent* event);

    public:
        StandardImageView(QWidget* parent, Image* image);
        //??? getClickedPixel();
        //ATTENTION A LA FUITE MEMOIRE !
        inline Image* getImage() const { return new Image(*_image); }
        inline QPixmap* getPixmap() const { return new QPixmap(*_pixmap_img); }
        inline Rectangle* getRectangle() const { return _selection; }
        inline QGraphicsView* getGraphicsView() const { return _view; }

	public slots:
        void ctrlPressed();
        void showHighlightRect(imagein::Rectangle* rect);
		
	signals:
		void pixelClicked(int x, int y);
		void pixelHovered(int x, int y);
		void zoomChanged(double z);
    };
}

#endif // STANDARDIMAGEVIEW_H
