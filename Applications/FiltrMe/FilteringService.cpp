#include "FilteringService.h"

#include <QMdiArea>

#include <GenericInterface.h>
#include <Converter.h>

using namespace filtrme;
using namespace genericinterface;
using namespace imagein::algorithm;

void FilteringService::display(GenericInterface* gi)
{
  QToolBar* toolBar = gi->addToolBar("Algorithms");
  _filtering = toolBar->addAction("&Filtering");
  _filterEdition = toolBar->addAction("&FilterEditor");
}

void FilteringService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);

  QObject::connect(_filtering, SIGNAL(triggered()), this, SLOT(applyFiltering()));
  QObject::connect(_filterEdition, SIGNAL(triggered()), this, SLOT(edition()));
}

void FilteringService::applyFiltering()
{  
  _filterChoice = new FilterChoice();
  QMdiArea* area = (QMdiArea*)_gi->centralWidget();  
  area->addSubWindow(_filterChoice);
  _filterChoice->show();
  
  QObject::connect(_filterChoice, SIGNAL(choiceValidate(imagein::algorithm::Filtering*)), this, SLOT(apply(imagein::algorithm::Filtering*)));
  QObject::connect(_filterChoice, SIGNAL(cancelAction()), this, SLOT(cancelAction()));  
}

void FilteringService::edition()
{  
  _filterEditor = new FilterEditor();
  QMdiArea* area = (QMdiArea*)_gi->centralWidget();  
  area->addSubWindow(_filterEditor);
  _filterEditor->show();
  
  QObject::connect(_filterEditor, SIGNAL(applyFiltering(imagein::algorithm::Filtering*)), this, SLOT(apply(imagein::algorithm::Filtering*))); 
  QObject::connect(_filterEditor, SIGNAL(cancelAction()), this, SLOT(cancelAction())); 
}

void FilteringService::cancelAction()
{
  ((QMdiArea*)_gi->centralWidget())->closeActiveSubWindow();
}

void FilteringService::apply(Filtering* filtering)
{
  ((QMdiArea*)_gi->centralWidget())->closeActiveSubWindow();
  
  applyAlgorithm(filtering);
}

void FilteringService::applyAlgorithm(Filtering* algo)
{
  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
  StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  if (siw != NULL)
  {
    const Image* im = siw->getImage();
    QString id = ws->getWidgetId(siw);
    Image_t<int>* im2 = Converter<Image>::convertToInt(*im);
    im2 = (*algo)(im2);
    Image* im_res = Converter<Image>::makeDisplayable(*im2);
    StandardImageWindow* siw_res = new StandardImageWindow("", _gi, im_res);
    emit newImageWindowCreated(id, siw_res);
  }
}
