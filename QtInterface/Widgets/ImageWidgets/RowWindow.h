#ifndef ROWWINDOW_H
#define ROWWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include <sstream>

#include "ImageWindow.h"
#include "RowView.h"

//#include "../../ImageIn/Image.h"
//using namespace imagein;

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
		RowWindow(bool vertical=false);
		//RowWindow(Image* image, StandardImageWindow* source, bool vertical=false);
    };
}

#endif // ROWWINDOW_H
