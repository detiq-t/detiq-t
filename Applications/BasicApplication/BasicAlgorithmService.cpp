/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "BasicAlgorithmService.h"
#include <GenericInterface.h>

#include <Algorithm/Identity.h>
#include <Algorithm/Inversion.h>

using namespace genericinterface;
using namespace imagein::algorithm;

void BasicAlgorithmService::display(GenericInterface* gi)
{
    AlgorithmService::display(gi);

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
