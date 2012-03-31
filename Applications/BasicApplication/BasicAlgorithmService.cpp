#include "BasicAlgorithmService.h"
#include "GenericInterface_r564/GenericInterface.h"

#include <Algorithm/Identity.h>
#include <Algorithm/Inversion.h>
#include <Algorithm/Average.h>


using namespace genericinterface;
using namespace imagein;
using namespace std;

void BasicAlgorithmService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);

  QObject::connect(_identity, SIGNAL(triggered()), this, SLOT(applyIdentity()));
  QObject::connect(_inversion, SIGNAL(triggered()), this, SLOT(applyInversion()));
  //QObject::connect(_average, SIGNAL(triggered()), this, SLOT(applyAverage()));

  WindowService* ws = dynamic_cast<WindowService*>(gi->getService(0));
  QObject::connect(this, SIGNAL(newImageWindowCreated(const QString&, ImageWindow*)), ws, SLOT(addWidget(const QString&, ImageWindow*)));
}

void BasicAlgorithmService::display(GenericInterface* gi)
{
  QToolBar* toolBar = gi->addToolBar("Algorithms");
  _identity = toolBar->addAction("&Identity");
  _inversion = toolBar->addAction("&Inversion");
  //_average = toolBar->addAction("&Average");
}

void BasicAlgorithmService::applyIdentity()
{
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(0));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
	 QString& path = siw->getPath();
    algorithm::Identity<Image> algo;
	 Image* im_res = algo(im);
    //std::cout << "Channels " << im_res->getNbChannels() << std::endl;
    //im_res->save("res.jpg");
	 StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
	 emit newImageWindowCreated(path, siw_res); 
  }
}

void BasicAlgorithmService::applyInversion()
{
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(0));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
	 QString& path = siw->getPath();
    algorithm::Inversion<Image> algo;
	 Image* im_res = algo(im);
	 StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
	 emit newImageWindowCreated(path, siw_res); 
  }
}

/*void BasicAlgorithmService::applyAverage()
{
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(0));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
	 QString& path = siw->getPath();
    algorithm::Average<Image> algo;
	 Image* im_res = algo(im);
	 StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
	 emit newImageWindowCreated(path, siw_res); 
  }
}*/
