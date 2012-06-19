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

#include "UtilityService.h"

using namespace genericinterface;
using namespace imagein;

void UtilityService::display(GenericInterface* gi)
{
	_gi = gi;

	//ajout des actions dans le menu show
	_showMenu = _gi->menu("&Show");
	_showHistogram = _showMenu->addAction("Histogram");
	_showHProjectionHistogram = _showMenu->addAction("Horizontal projection histogram");
	_showVProjectionHistogram = _showMenu->addAction("Vertical projection histogram");
	_showPixelsGrid = _showMenu->addAction("Pixels grid");
	
	_showHistogram->setEnabled(false);
	_showHProjectionHistogram->setEnabled(false);
	_showVProjectionHistogram->setEnabled(false);
	_showPixelsGrid->setEnabled(false);
}

void UtilityService::connect(GenericInterface* gi)
{
	//Connexion des actions
	QObject::connect(_showHistogram, SIGNAL(triggered()), this, SLOT(showHistogram()));
	QObject::connect(_showHProjectionHistogram, SIGNAL(triggered()), this, SLOT(showHProjectionHistogram()));
	QObject::connect(_showVProjectionHistogram, SIGNAL(triggered()), this, SLOT(showVProjectionHistogram()));
	QObject::connect(_showPixelsGrid, SIGNAL(triggered()), this, SLOT(showPixelsGrid()));
	
	//connexion des changements d'images
	WindowService* ws = dynamic_cast<WindowService*>(gi->getService(GenericInterface::WINDOW_SERVICE));
	QObject::connect(ws, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(checkActionsValid(QMdiSubWindow*)));
}

void UtilityService::showHistogram()
{
	WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
	StandardImageWindow* curWindow = NULL;
	
	if(ws && (curWindow = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow()))) {
		curWindow->showHistogram();
	}
}

void UtilityService::showHProjectionHistogram()
{
	WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
	StandardImageWindow* curWindow = NULL;
	
	if(ws && (curWindow = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow()))) {
			curWindow->showHProjectionHistogram();
	}
}

void UtilityService::showVProjectionHistogram()
{
	WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
	StandardImageWindow* curWindow = NULL;
	
	if(ws && (curWindow = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow()))) {
		curWindow->showVProjectionHistogram();
	}
}

void UtilityService::showPixelsGrid()
{
	WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
	StandardImageWindow* curWindow = NULL;
	
	if(ws && (curWindow = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow()))) {
		curWindow->showPixelsGrid();
	}
}

void UtilityService::checkActionsValid(QMdiSubWindow* activeWindow)
{
	StandardImageWindow* window = (activeWindow) ? dynamic_cast<StandardImageWindow*>(activeWindow->widget()) : NULL;
	if(window) {
		_showHistogram->setEnabled(true);
		_showHProjectionHistogram->setEnabled(true);
		_showVProjectionHistogram->setEnabled(true);
		_showPixelsGrid->setEnabled(true);
	}
	else {
		_showHistogram->setEnabled(false);
		_showHProjectionHistogram->setEnabled(false);
		_showVProjectionHistogram->setEnabled(false);
		_showPixelsGrid->setEnabled(false);
	}
}