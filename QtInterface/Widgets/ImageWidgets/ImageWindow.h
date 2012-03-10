#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <iostream>

#include <Rectangle.h>

namespace genericinterface
{
	class ImageWindow : public QWidget
    {
		Q_OBJECT
    protected:
        imagein::Rectangle* _applicationArea;
        QStatusBar* _statusBar;
        ImageWindow* _sourceWindow;
        QString _path; /*!< The path of the source image */

    public:
        ImageWindow(ImageWindow* source = NULL, imagein::Rectangle* rect = NULL);
        
    public slots:
		void activated();
	
	signals:
		void highlightRectChange(imagein::Rectangle*);
    };
}

#endif // IMAGEWINDOW_H
