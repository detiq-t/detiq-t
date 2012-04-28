#include "ImageWindow.h"

using namespace genericinterface;
using namespace imagein;

ImageWindow::ImageWindow(const ImageWindow* source, Rectangle* rect): QWidget(), _sourceWindow(source)
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

void ImageWindow::setApplicationArea(const imagein::Rectangle* rect)
{
  _applicationArea->x = rect->x;
  _applicationArea->y = rect->y;
  _applicationArea->w = rect->w;
  _applicationArea->h = rect->h;
}
    
QString& ImageWindow::getPath()
{
  return _path;
}
