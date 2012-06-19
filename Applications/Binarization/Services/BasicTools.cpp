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

#include "BasicTools.h"
#include <GenericInterface.h>

#include <Algorithm/Identity.h>
#include <Algorithm/Inversion.h>
#include <Algorithm/RgbToGrayscale.h>
#include <Converter.h>

using namespace genericinterface;
using namespace imagein;
using namespace imagein::algorithm;

void BasicTools::display(GenericInterface* gi)
{
    AlgorithmService::display(gi);

    _menu = gi->menu("&Basic Tools");

    _identity = _menu->addAction("&Clone the current image");
    _inversion = _menu->addAction("&Make an inversion of the current image");
    _convertToGrayscale = _menu->addAction("&Convert to a grayscale image");
}

void BasicTools::connect(GenericInterface* gi)
{
    AlgorithmService::connect(gi);

    QObject::connect(_identity, SIGNAL(triggered()), this, SLOT(applyIdentity()));
    QObject::connect(_inversion, SIGNAL(triggered()), this, SLOT(applyInversion()));
    QObject::connect(_convertToGrayscale, SIGNAL(triggered()), this, SLOT(convertToGrayscale()));
}


void BasicTools::applyIdentity()
{
    Identity<Image>* algo = new Identity<Image>;
    applyAlgorithm(algo);
}

void BasicTools::applyInversion()
{
    Inversion<Image>* algo = new Inversion<Image>;
    applyAlgorithm(algo);
}

void BasicTools::convertToGrayscale()
{
    RgbToGrayscale* algo = new RgbToGrayscale;
    applyAlgorithm(algo);
}
