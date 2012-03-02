#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>

//#include <Rectangle.h>
//#include <Image.h>

//using namespace imagein;

namespace genericinterface
{
    class StandardImageWindow;
    class ImageWindow : public QWidget
    {
    protected:
        //Rectangle* _applicationArea;
        QStatusBar* _statusBar;
        StandardImageWindow* _sourceWindow;
    public:
        ImageWindow();
        ImageWindow(StandardImageWindow* source);
    };
}

#endif // IMAGEWINDOW_H
