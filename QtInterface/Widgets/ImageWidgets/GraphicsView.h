#ifndef GraphicsView_H
#define GraphicsView_H

#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

#include <Image.h>

namespace genericinterface
{
	class GraphicsView : public QGraphicsView
	{
		Q_OBJECT
	private:
		QGraphicsScene* _scene;
		QGraphicsPixmapItem* _item;
		QPixmap* _pixmap_img;
		imagein::Image* _image;
		
		void init();
		void showPixelsGrid();
		
        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);
        void wheelEvent(QWheelEvent* event);
		
	public:
		GraphicsView(imagein::Image* image);
        
	signals:
		void pixelClickedLeft(int x, int y);
		void pixelClickedRight(int x, int y);
		void pixelHovered(int x, int y);
	};
}

#endif //GraphicsView_H
