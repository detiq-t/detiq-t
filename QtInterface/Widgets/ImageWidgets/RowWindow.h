#ifndef ROWWINDOW_H
#define ROWWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include <sstream>

#include "ImageWindow.h"
#include "RowView.h"

#include <Image.h>

namespace genericinterface
{
    class RowWindow : public ImageWindow
    {
		Q_OBJECT
    private:
        RowView* _view;
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
		RowWindow(imagein::Image* image, StandardImageWindow* source, imagein::Histogram* histogram, bool vertical=false);
    };
}

#endif // ROWWINDOW_H
