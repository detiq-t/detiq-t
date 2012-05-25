#include "ImageWindow.h"

using namespace genericinterface;
using namespace imagein;

ImageWindow::ImageWindow(const QString & path, const ImageWindow* source, Rectangle* rect): QWidget(), _sourceWindow(source), _path(path)
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

std::string ImageWindow::getTitleFromPath(const QString & path)
{
  std::string p = path.toStdString();
  size_t pos = p.rfind("\\");
  if(pos != std::string::npos)
    p = p.substr(pos + 1);
  else if((pos = p.rfind("/")) != std::string::npos)
    p = p.substr(pos + 1);
    
  return p;
}

QString ImageWindow::getName()
{
    QString res = QString::fromStdString(getTitleFromPath(_path));
    return res;
}
