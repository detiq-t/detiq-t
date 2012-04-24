#include "BinarizationService.h"
#include <GenericInterface.h>

#include <Algorithm/Binarization.h>
#include <Algorithm/Otsu.h>
#include <Converter.h>

#include <QMessageBox>

using namespace genericinterface;
using namespace imagein::algorithm;

void BinarizationService::display(GenericInterface* gi)
{
  AlgorithmService::display(gi);

  _toolBar = gi->addToolBar("Binarization");
  _otsu = _toolBar->addAction("&Otsu");
  _manual = _toolBar->addAction("&Manual binarization");
}

void BinarizationService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);

  QObject::connect(_otsu, SIGNAL(triggered()), this, SLOT(applyOtsu()));
  QObject::connect(_manual, SIGNAL(triggered()), this, SLOT(applyManualBinarization()));
}


void BinarizationService::applyOtsu()
{
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
	 QString& path = siw->getPath();
    Otsu algo;
    GrayscaleImage* im_tmp = Converter<GrayscaleImage>::convert(*im);
    Image* im_res = algo(im_tmp);
    StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
    emit newImageWindowCreated(path, siw_res);
  } 
}


void BinarizationService::applyManualBinarization()
{

}
