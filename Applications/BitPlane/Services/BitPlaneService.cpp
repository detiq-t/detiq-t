/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-T�tu, Florian Teyssier
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

#include "BitPlaneService.h"

using namespace genericinterface;
using namespace imagein;
using namespace algorithm;

void BitPlaneService::display(GenericInterface* gi)
{
    AlgorithmService::display(gi);

    _bitplane = _toolBar->addAction("&Bit plane");
}

void BitPlaneService::connect(GenericInterface* gi)
{
    AlgorithmService::connect(gi);

    QObject::connect(_bitplane, SIGNAL(triggered()), this, SLOT(applyBitPlane()));
}


void BitPlaneService::applyBitPlane()
{ 
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* im = siw->getImage();
        Image* im_selected = im->crop(*(siw->getSelection()));
        QString id = _ws->getWidgetId(siw);
        _bitplanewindow = new BitPlaneWindow("", _gi, im_selected);
        emit newImageWindowCreated(id, _bitplanewindow);
    }
}
