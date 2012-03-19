#include "IdentityAlgorithmService.h"
#include "../GenericInterface.h"
#include <Algorithm/Identity.h>
#include <vector>

using namespace genericinterface;
using namespace imagein;
using namespace std;

void IdentityAlgorithmService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);
  QObject::connect(_apply, SIGNAL(triggered()), this, SLOT(apply()));

  WindowService* ws = dynamic_cast<WindowService*>(gi->getService(0));
  QObject::connect(this, SIGNAL(newImageWindowCreated(const QString&, ImageWindow*)), ws, SLOT(addWidget(const QString&, ImageWindow*)));
}

void IdentityAlgorithmService::display(GenericInterface* gi)
{
  QToolBar* toolBar = gi->addToolBar("Identity");
  _apply = toolBar->addAction("&Apply");
}

void IdentityAlgorithmService::apply()
{
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(0));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
	 QString& path = siw->getPath();
    algorithm::Identity< uint8_t, Image_t> algo; // = new algorithm::Identity<uint8_t, Image_t>();
    Image* im_res = algo(im);
	 StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
	 emit newImageWindowCreated(path, siw_res); 
  }
}
