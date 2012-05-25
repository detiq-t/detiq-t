#include "BitPlaneService.h"

using namespace genericinterface;
using namespace imagein;
using namespace algorithm;

void BitPlaneService::display(GenericInterface* gi)
{
  QToolBar* toolBar = gi->addToolBar("Algorithms");
  _bitplane = toolBar->addAction("&Bit plane");
}

void BitPlaneService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);

  QObject::connect(_bitplane, SIGNAL(triggered()), this, SLOT(applyBitPlane()));
}


void BitPlaneService::applyBitPlane()
{ 
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
    Image* im_selected = im->crop(*(siw->getSelection()));
    QString id = ws->getWidgetId(siw);
    _bitplanewindow = new BitPlaneWindow("", _gi, im_selected);
    emit newImageWindowCreated(id, _bitplanewindow);
  }
}
