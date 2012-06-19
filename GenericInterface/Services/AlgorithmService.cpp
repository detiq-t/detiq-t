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

#include "AlgorithmService.h"
#include "../GenericInterface.h"

#include <Converter.h>

using namespace genericinterface;
using namespace imagein;

AlgorithmService::AlgorithmService()
{

}

void AlgorithmService::display(GenericInterface* gi)
{
  _toolBar = gi->toolBar("Algorithm");
}

void AlgorithmService::connect(GenericInterface* gi)
{
  _gi = gi;
  _ws = _gi->windowService();

  QObject::connect(this, SIGNAL(newImageWindowCreated(const QString&, ImageWindow*)), _ws, SLOT(addImage(const QString&, ImageWindow*)));
}

void AlgorithmService::applyAlgorithm(GenericAlgorithm_t<Image::depth_t>* algo)
{
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* whole_image = siw->getImage();
        const Image* im = whole_image->crop(*(siw->getSelection()));
        QString name = _ws->getWidgetId(siw);

        Image* im_res = (*algo)(im);
        //im_res = Converter<Image>::makeDisplayable(*im_res);

        StandardImageWindow* siw_res = new StandardImageWindow(name, _gi, im_res);
        emit newImageWindowCreated(name, siw_res);
    }
}
