#include "ImageWindow.h"

using namespace genericinterface;
using namespace imagein;

ImageWindow::ImageWindow(ImageWindow* source, Rectangle* rect): QWidget(), _sourceWindow(source), _applicationArea(rect)
{
    _statusBar = new QStatusBar();
}
