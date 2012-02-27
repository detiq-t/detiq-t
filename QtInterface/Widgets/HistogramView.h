#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QMouseEvent>

#include "AlternativeImageView.h"
//#include "../../ImageIn/Image.h"

//using namespace imagein;

namespace genericinterface
{
    class HistogramView : public AlternativeImageView
    {
		Q_OBJECT
	private:
		void init();
        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);
	
    public:
		HistogramView();
		//HistogramView(QWidget* parent, Image* image);
        int getMemorisedValue(int i);
        void setMemorisedValue(int i, int value);
		
	signals:
		void valueClickedLeft(int value);
		void valueClickedRight(int value);
		void valueHovered(int value);
    };
}

#endif // HISTOGRAMVIEW_H
