#ifndef STANDARDIMAGEWINDOW_H
#define STANDARDIMAGEWINDOW_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QScrollArea>
#include <QFont>
#include <QKeyEvent>

#include <sstream>
#include <iostream>

#include "ImageWindow.h"
#include "HistogramWindow.h"
#include "StandardImageView.h"
#include "GridWindow.h"
#include "RowWindow.h"

#include "../../ImageIn/Image.h"
#include "../../ImageIn/Rectangle.h"

using namespace imagein;

namespace genericinterface
{
    class StandardImageWindow : public ImageWindow
    {
		Q_OBJECT
    private:
		QMdiArea* _area;
        StandardImageView* _imageView;
        QLabel* _lImageSize;
        QLabel* _lImageName;
        QLabel* _lHoveredPixelInfo;
        QLabel* _lHoveredPixelPosition;
        QLabel* _lHoveredPixelColor;
        QLabel* _lSelectedPixelInfo;
        QLabel* _lSelectedPixelPosition;
        QLabel* _lSelectedPixelColor;
        QLabel* _lZoom;
        
		void init();
        void initStatusBar();
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);
    
    public slots:
        void showHistogram(Rectangle* rect = NULL);
        void showPixelsGrid();
        void showLineProfile();
        void showColumnProfile();
        //void highlightRect(Rectangle* rect);
        void showHoveredPixelInformations(int x, int y);
        void showSelectedPixelInformations(int x, int y);
        void updateZoom(double z);
        
	signals:
		void ctrlPressed();

    public:
        StandardImageWindow(QMdiArea* area);
        StandardImageWindow(QMdiArea* area, QString file);
        StandardImageWindow(QMdiArea* area, Image* image);
        StandardImageWindow(QMdiArea* area, Image* image, StandardImageWindow* source);
    };
}

#endif // STANDARDIMAGEWINDOW_H
