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

#include "FilteringService.h"

#include <QMdiArea>

#include <GenericInterface.h>
#include <Converter.h>

using namespace filtrme;
using namespace genericinterface;
using namespace imagein::algorithm;

void FilteringService::display(GenericInterface* gi)
{
    AlgorithmService::display(gi);

    _filtering = _toolBar->addAction("&Filtering");
    _filterEdition = _toolBar->addAction("&FilterEditor");
}

void FilteringService::connect(GenericInterface* gi)
{
    AlgorithmService::connect(gi);

    QObject::connect(_filtering, SIGNAL(triggered()), this, SLOT(applyFiltering()));
    QObject::connect(_filterEdition, SIGNAL(triggered()), this, SLOT(edition()));
}

void FilteringService::applyFiltering()
{
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        _siw = siw;

        _filterChoice = new FilterChoice();
        QMdiArea* area = (QMdiArea*)_gi->centralWidget();
        area->addSubWindow(_filterChoice);
        _filterChoice->show();

        QObject::connect(_filterChoice, SIGNAL(choiceValidate(imagein::algorithm::Filtering*)), this, SLOT(apply(imagein::algorithm::Filtering*)));
        QObject::connect(_filterChoice, SIGNAL(cancelAction()), this, SLOT(cancelAction()));
    }
}

void FilteringService::edition()
{  
    _filterEditor = new FilterEditor();
    //QMdiArea* area = (QMdiArea*)_gi->centralWidget();
    //area->addSubWindow(_filterEditor);
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    _ws->addWidget(_ws->getWidgetId(siw), _filterEditor);
    //_filterEditor->show();

    QObject::connect(_filterEditor, SIGNAL(applyFiltering(imagein::algorithm::Filtering*)), this, SLOT(apply(imagein::algorithm::Filtering*)));
    QObject::connect(_filterEditor, SIGNAL(cancelAction()), this, SLOT(cancelAction()));
}

void FilteringService::cancelAction()
{
    ((QMdiArea*)_gi->centralWidget())->closeActiveSubWindow();
}

void FilteringService::apply(Filtering* filtering)
{
    ((QMdiArea*)_gi->centralWidget())->closeActiveSubWindow();

    applyAlgorithm(filtering);
}

void FilteringService::applyAlgorithm(Filtering* algo)
{
    //StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    if (_siw != NULL)
    {
        const Image* whole_image = _siw->getImage();
        const Image* im = whole_image->crop(*(_siw->getSelection()));
        QString id = _ws->getWidgetId(_siw);
        Image_t<int>* im2 = Converter<Image>::convertToInt(*im);
        im2 = (*algo)(im2);
        Image* im_res = Converter<Image>::makeDisplayable(*im2);
        StandardImageWindow* siw_res = new StandardImageWindow(id, _gi, im_res);
        siw_res->setWindowTitle(ImageWindow::getTitleFromPath(_siw->getPath()));
        emit newImageWindowCreated(id, siw_res);
    }
}
