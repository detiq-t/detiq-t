#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <iostream>

#include <Rectangle.h>
//#include <Image.h>

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
        ImageWindow(ImageWindow* source = NULL, imagein::Rectangle* rect = new imagein::Rectangle());
    };
}

#endif // IMAGEWINDOW_H
