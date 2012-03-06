#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QString>

//#include <Rectangle.h>
//#include <Image.h>

namespace genericinterface
{
    //class StandardImageWindow;
    class ImageWindow : public QWidget
    {
    protected:
        //Rectangle* _applicationArea;
        QStatusBar* _statusBar;
        ImageWindow* _sourceWindow;
        QString _path; /*!< The path of the source image */

    public:
        ImageWindow();
        ImageWindow(ImageWindow* source);
    };
}

#endif // IMAGEWINDOW_H
