#include "BitPlaneService.h"
#include <GenericInterface.h>

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
  _bitplanechoice = new BitPlaneChoice();
  _bitplanechoice->show();

   QObject::connect(_bitplanechoice, SIGNAL(choiceValidate(imagein::algorithm::BitPlane<imagein::Image>*)), this, SLOT(apply(imagein::algorithm::BitPlane<imagein::Image>*))); 
}

void BitPlaneService::apply(imagein::algorithm::BitPlane<imagein::Image>* bitplanealgo)
{
  applyAlgorithm(bitplanealgo);
}
