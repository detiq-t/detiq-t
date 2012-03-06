#include "ImageWindow.h"

using namespace genericinterface;

ImageWindow::ImageWindow(): QWidget(), _sourceWindow(0)
{
    //_applicationArea = new Rectangle();
    _statusBar = new QStatusBar();
}

ImageWindow::ImageWindow(ImageWindow* source): QWidget(), _sourceWindow(source)
{
    //_applicationArea = new Rectangle();
    _statusBar = new QStatusBar();
}
