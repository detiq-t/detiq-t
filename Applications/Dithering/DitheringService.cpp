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

#include "DitheringService.h"
#include <GenericInterface.h>
#include <GrayscaleImage.h>

#include <Converter.h>
#include <Algorithm/Dithering.h>

using namespace genericinterface;
using namespace imagein;
using namespace imagein::algorithm;


void DitheringService::display(GenericInterface* gi)
{
    AlgorithmService::display(gi);

    _dithering = _toolBar->addAction("&Dithering");
}

void DitheringService::connect(GenericInterface* gi)
{
    AlgorithmService::connect(gi);

    QObject::connect(_dithering, SIGNAL(triggered()), this, SLOT(applyDithering()));
}


void DitheringService::applyDithering()
{ 
    Dithering* algo = new Dithering;
    applyAlgorithm(algo);
    return;
    
	//StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    //if (siw != NULL)
    //{
        //const Image* whole_image = siw->getImage();
        //const Image* im = whole_image->crop(*(siw->getSelection()));
        //QString name = _ws->getWidgetId(siw);

        //Image* im_res = (*algo)(Converter<GrayscaleImage>::convert(*im));
        ////im_res = Converter<Image>::makeDisplayable(*im_res);

        //StandardImageWindow* siw_res = new StandardImageWindow(name, _gi, im_res);
        //emit newImageWindowCreated(name, siw_res);
    //}
}
