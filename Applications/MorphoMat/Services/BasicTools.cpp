#include "BasicTools.h"
#include <GenericInterface.h>

#include <Algorithm/Identity.h>
#include <Algorithm/Inversion.h>
#include <Converter.h>

using namespace genericinterface;
using namespace imagein;
using namespace imagein::algorithm;

void BasicTools::display(GenericInterface* gi)
{
  _menu = gi->menu("&Basic Tools");

  _identity = _menu->addAction("&Clone the current image");
  _inversion = _menu->addAction("&Make an inversion of the current image");
  _convertToGrayscale = _menu->addAction("&Convert to a grayscale image");
}

void BasicTools::connect(GenericInterface* gi)
{
  QObject::connect(_identity, SIGNAL(triggered()), this, SLOT(applyIdentity()));
  QObject::connect(_inversion, SIGNAL(triggered()), this, SLOT(applyInversion()));
  QObject::connect(_convertToGrayscale, SIGNAL(triggered()), this, SLOT(convertToGrayscale()));
}


void BasicTools::applyIdentity()
{
}

void BasicTools::applyInversion()
{
}

void BasicTools::convertToGrayscale()
{
}
