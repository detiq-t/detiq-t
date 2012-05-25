#include "BasicAlgorithmService.h"
#include <GenericInterface.h>

#include <Algorithm/Identity.h>
#include <Algorithm/Inversion.h>

using namespace genericinterface;
using namespace imagein::algorithm;

void BasicAlgorithmService::display(GenericInterface* gi)
{
    AlgorithmService::display(gi);

    _toolBar = gi->addToolBar("Basic Algorithms");
    _identity = _toolBar->addAction("&Identity");
    _inversion = _toolBar->addAction("&Inversion");
}

void BasicAlgorithmService::connect(GenericInterface* gi)
{
    AlgorithmService::connect(gi);

    QObject::connect(_identity, SIGNAL(triggered()), this, SLOT(applyIdentity()));
    QObject::connect(_inversion, SIGNAL(triggered()), this, SLOT(applyInversion()));
}


void BasicAlgorithmService::applyIdentity()
{ 
    Identity<Image>* algo = new Identity<Image>;
    applyAlgorithm(algo);
}

void BasicAlgorithmService::applyInversion()
{
    Inversion<Image>* algo = new Inversion<Image>;
    applyAlgorithm(algo);
}
