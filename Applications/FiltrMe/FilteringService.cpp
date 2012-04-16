#include "FilteringService.h"

#include <QMdiArea>

#include <GenericInterface.h>

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
  applyAlgorithm(filtering);
}
