#include "AlgorithmService.h"
#include "../GenericInterface.h"

using namespace genericinterface;
using namespace imagein;

AlgorithmService::AlgorithmService()
{

}

void AlgorithmService::display(GenericInterface* gi)
{
  _toolBar = gi->addToolBar("Algorithm");
}

void AlgorithmService::connect(GenericInterface* gi)
{
  _gi = gi;

  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(0));
  QObject::connect(this, SIGNAL(newImageWindowCreated(const QString&, ImageWindow*)), ws, SLOT(addWidget(const QString&, ImageWindow*)));
}

void AlgorithmService::applyAlgorithm(Algorithm_t<Image>* algo)
{
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(0));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
	 QString& path = siw->getPath();
	 Image* im_res = (*algo)(im);
	 StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
	 emit newImageWindowCreated(path, siw_res); 
  }
}
