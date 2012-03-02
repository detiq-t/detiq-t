#ifndef ROWVIEW_H
#define ROWVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QMouseEvent>

#include "AlternativeImageView.h"

//#include <Image.h>
//using namespace imagein;

namespace genericinterface
{
    class RowView : public AlternativeImageView
    {
		Q_OBJECT
	private:
        bool _vertical;
		void init();
        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);

    public:
		RowView(bool v=0);
        //RowView(QWidget* parent, Image* image, bool v=0);
		
	signals:
		void valueClickedLeft(int value);
		void valueClickedRight(int value);
		void valueHovered(int value);
    };
}

#endif // ROWVIEW_H
