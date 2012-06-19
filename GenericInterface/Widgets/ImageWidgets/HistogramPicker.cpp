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

#include "HistogramPicker.h"

using namespace genericinterface;

HistogramPicker::HistogramPicker(QwtPlotCanvas* canvas): QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, canvas) {}

HistogramPicker::HistogramPicker(RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas* canvas): QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, rubberBand, trackerMode, canvas) {}

QwtText HistogramPicker::trackerTextF(const QPointF& pos) const
{
	QPointF p = QPointF(pos.x(), pos.y());
    emit(moved(p));
    
    QString label;	
	label.sprintf("%d", (int)pos.x());    
    return label;
}
