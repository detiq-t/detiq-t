#ifndef STANDARDIMAGEVIEW_H
#define STANDARDIMAGEVIEW_H

#include <QLabel>
#include <QString>
#include <QMouseEvent>
#include <QWheelEvent>
#include <iostream>

#include "ImageContextMenu.h"

#include "../../ImageIn/Image.h"
#include "../../ImageIn/Rectangle.h"

using namespace imagein;

namespace genericinterface
{
    class StandardImageView : public QLabel
    {
		Q_OBJECT
    private:
		QWidget* _parent;
		QPixmap* _pixmap_img;
		double _zoomFactor;
        Image* _image;
        Rectangle* _highlight;
        Rectangle* _selection;
        Rectangle* _visibleArea;
        ImageContextMenu* _menu;
        void init();
        void initMenu();
        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);
        void wheelEvent(QWheelEvent* event);
        void showImage();

    public:
        StandardImageView(QWidget* parent);
        StandardImageView(QWidget* parent, QString file);
        StandardImageView(QWidget* parent, Image* image);
        //??? getClickedPixel();
        //inline Image* getImage() const {return new Image(*_image);}
        inline QPixmap* getImage() const {return new QPixmap(*_pixmap_img);}

	public slots:
        //void showRectangle(Rectangle* rect);
		
	signals:
		void pixelClicked(int x, int y);
		void pixelHovered(int x, int y);
    };
}

#endif // STANDARDIMAGEVIEW_H
