#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QMouseEvent>

#include "AlternativeImageView.h"

//#include <Image.h>
//using namespace imagein;

namespace genericinterface
{
    class GridView : public AlternativeImageView
    {
		Q_OBJECT
	private:
		void init();
        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);
        
	public:
		GridView();
		//GridView(QWidget* parent, Image* image);
		
	signals:
		void pixelClickedLeft(int x, int y);
		void pixelClickedRight(int x, int y);
		void pixelHovered(int x, int y);
    };
}

#endif // GRIDVIEW_H
