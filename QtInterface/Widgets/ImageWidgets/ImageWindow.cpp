#include "ImageWindow.h"

using namespace genericinterface;

ImageWindow::ImageWindow(): QWidget(), _sourceWindow(NULL)
{
    //_applicationArea = new Rectangle();
    _statusBar = new QStatusBar();
}

ImageWindow::ImageWindow(StandardImageWindow* source): QWidget(), _sourceWindow(source)
{
    //_applicationArea = new Rectangle();
    _statusBar = new QStatusBar();
}
