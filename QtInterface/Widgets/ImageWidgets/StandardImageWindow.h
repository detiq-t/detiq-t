#ifndef STANDARDIMAGEWINDOW_H
#define STANDARDIMAGEWINDOW_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QScrollArea>
#include <QFont>
#include <QKeyEvent>
#include <QPoint>

#include <sstream>
#include <iostream>
#include <list>

#include "ImageWindow.h"
#include "HistogramWindow.h"
#include "StandardImageView.h"
#include "GridWindow.h"
#include "RowWindow.h"

#include "../../GenericInterface.h"

#include <Image.h>
#include <Rectangle.h>
#include <Histogram.h>

#include <QString>

namespace genericinterface
{
    class StandardImageWindow : public ImageWindow
    {
		Q_OBJECT
    private:
        GenericInterface* _gi;

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
        QPoint* _selectedPixel;
        bool _isRootImage;

        void init();
        void initStatusBar();
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);
   
    protected:
	     void closeEvent(QCloseEvent* event);

    public slots:
        void showHistogram();

        void showPixelsGrid();
        void showLineProfile();
        void showColumnProfile();
        void showHoveredPixelInformations(int x, int y);
        void showSelectedPixelInformations(int x, int y);
        void updateZoom(double z);
        
        void showHighlightRect(imagein::Rectangle* rect);
        
	signals:
		void ctrlPressed();
		void highlightRectChange(imagein::Rectangle*);    

    public:
        StandardImageWindow(const QString & path, GenericInterface* gi);
        std::list<HistogramWindow*> getHistogram();
		  void setAsRoot();
    };
}

#endif // STANDARDIMAGEWINDOW_H
