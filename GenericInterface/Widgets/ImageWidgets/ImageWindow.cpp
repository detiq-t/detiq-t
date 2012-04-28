#include "ImageWindow.h"

using namespace genericinterface;
using namespace imagein;

ImageWindow::ImageWindow(const ImageWindow* source, const Rectangle* rect): QWidget(), _sourceWindow(source)
{
	if(rect)
		_applicationArea = new Rectangle(*rect);
	else
		_applicationArea = new Rectangle();
    _statusBar = new QStatusBar();
}

void ImageWindow::activated()
{
	emit(highlightRectChange(_applicationArea, this));
}

QString& ImageWindow::getPath()
{
  return _path;
}
