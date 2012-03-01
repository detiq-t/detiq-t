#ifndef GRIDWINDOW_H
#define GRIDWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFont>

#include <sstream>

#include "ImageWindow.h"
#include "GridView.h"

//#include "../../ImageIn/Image.h"
//using namespace imagein;

namespace genericinterface
{
    class GridWindow : public ImageWindow
    {
		Q_OBJECT
    private:
        GridView* _view;
		QLabel* _lImageName;
		QLabel* _lHoveredPixelInfo;
		QLabel* _lSelectedPixel1Info;
		QLabel* _lSelectedPixel2Info;
		QLabel* _lHoveredPixelPosition;
		QLabel* _lHoveredPixelColor;
		QLabel* _lSelectedPixel1Position;
		QLabel* _lSelectedPixel2Position;
		QLabel* _lSelectedPixel1Color;
		QLabel* _lSelectedPixel2Color;
		
		void init();
        void initStatusBar();
        
    public slots:
		void showHoveredPixel(int x, int y);
        void showLeftClickedPixel(int x, int y);
        void showRightClickedPixel(int x, int y);
        
    public:
		GridWindow();
		//GridWindow(Image* image, StandardImageWindow* source);
    };
}

#endif // GRIDWINDOW_H
