#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFont>

#include <sstream>

#include "ImageWindow.h"
#include "HistogramView.h"

//#include "../../ImageIn/Image.h"
//using namespace inmagein;

namespace genericinterface
{
    class HistogramWindow : public ImageWindow
    {
		Q_OBJECT
    private:
        HistogramView* _view;
		QLabel* _lImageName;
		QLabel* _lHoveredValue;
		QLabel* _lSelectedValue1;
		QLabel* _lSelectedValue2;
		
		void init();
        void initStatusBar();
        
    public slots:
		void showHoveredValue(int value);
        void showLeftClickedValue(int value);
        void showRightClickedValue(int value);
        
    public:
		HistogramWindow();
		//HistogramWindow(Image* image, StandardImageWindow* source);
    };
}

#endif // HISTOGRAMWINDOW_H
