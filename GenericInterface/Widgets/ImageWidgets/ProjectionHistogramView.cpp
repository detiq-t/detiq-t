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

#include "ProjectionHistogramView.h"

using namespace genericinterface;
using namespace imagein;

ProjectionHistogramView::ProjectionHistogramView(const Image* image, Rectangle* rect, int value, bool horizontal): GenericHistogramView(image, rect, true, horizontal, value)
{
    _qwtPlot->setTitle("Projection Histogram");

    _qwtPlot->setAxisTitle(QwtPlot::yLeft, "");
    _qwtPlot->setAxisTitle(QwtPlot::xBottom, "");
}

void ProjectionHistogramView::showItem(QwtPlotItem *item, bool on) const
{
    item->setVisible(on);
}

void ProjectionHistogramView::leftClick(const QPointF& pos) const
{
	if(_horizontal)
		emit(leftClickedValue((int)pos.y()));
	else
		emit(leftClickedValue((int)pos.x()));
}

void ProjectionHistogramView::rightClick(const QPointF& pos) const
{
    if(_horizontal)
		emit(rightClickedValue((int)pos.y()));
	else
		emit(rightClickedValue((int)pos.x()));
}

void ProjectionHistogramView::move(const QPointF& pos) const
{
	if(_horizontal)
		emit(hoveredValue((int)pos.y()));
	else
		emit(hoveredValue((int)pos.x()));
}

