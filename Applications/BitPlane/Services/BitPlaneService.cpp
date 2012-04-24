#include "BitPlaneService.h"
#include <GenericInterface.h>

#include <Algorithm/BitPlane.h>

using namespace genericinterface;
using namespace imagein::algorithm;

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
  //Identity<Image>* algo = new Identity<Image>;
  //applyAlgorithm(algo);
}
