#include "FilteringService.h"

#include <QMdiArea>

#include <GenericInterface.h>
#include <Converter.h>

using namespace genericinterface;
using namespace imagein::algorithm;

void FilteringService::display(GenericInterface* gi)
{
  QToolBar* toolBar = gi->addToolBar("Algorithms");
  _filtering = toolBar->addAction("&Filtering");
}

void FilteringService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);

  QObject::connect(_filtering, SIGNAL(triggered()), this, SLOT(applyFiltering()));
}

void FilteringService::applyFiltering()
{  
  _filterChoice = new FilterChoice();
  QMdiArea* area = (QMdiArea*)_gi->centralWidget();  
  area->addSubWindow(_filterChoice);
  _filterChoice->show();
  
  QObject::connect(_filterChoice, SIGNAL(choiceValidate(imagein::algorithm::Filtering*)), this, SLOT(apply(imagein::algorithm::Filtering*))); 
}

void FilteringService::apply(Filtering* filtering)
{
  ((QMdiArea*)_gi->centralWidget())->closeActiveSubWindow();
  
  /*#ifdef __linux__
    pthread_t thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    struct ThreadArgs* args = new struct ThreadArgs;
    args->filtering = filtering;
    args->gi = _gi;
    
    pthread_create(&thread, &attr, parallelAlgorithm, (void*)args);
  #else*/
    applyAlgorithm(filtering);
  //#endif
}

void FilteringService::applyAlgorithm(Filtering* algo)
{
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
    QString& path = siw->getPath();
    Image_t<int>* im2 = Converter<Image>::convertToInt(*im);
    im2 = (*algo)(im2);
    Image* im_res = Converter<Image>::makeDisplayable(*im2);
    StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
    emit newImageWindowCreated(path, siw_res);
  }
}

/*void* FilteringService::parallelAlgorithm(void* data)
{
  struct ThreadArgs args = *((ThreadArgs*) data);
	
  GenericInterface* gi = args.gi;
  Filtering* algo = args.filtering;
  
  WindowService* ws = dynamic_cast<WindowService*>(gi->getService(GenericInterface::WINDOW_SERVICE));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
    QString& path = siw->getPath();
    Image_t<int>* im2 = Converter<Image>::convertToInt(*im);
    im2 = (*algo)(im2);
    Image* im_res = Converter<Image>::makeDisplayable(*im2);
    StandardImageWindow* siw_res = new StandardImageWindow(path, gi, im_res);
    ws->addWidget(path, siw_res);
    emit newImageWindowCreated(path, siw_res);
  }
  
  delete (ThreadArgs*) data;
  pthread_exit(NULL);
}
*/
