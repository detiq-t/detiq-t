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

#ifndef HISTOGRAMPICKER_H
#define HISTOGRAMPICKER_H

#include <QPainter>

#include <qwt_plot.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_canvas.h>

namespace genericinterface
{
	/*!
     * \brief Management of mouse events on a histogram
     * 
     * A special object inherit from QwtPlotPicker is required to manage mouse events.
     * This class manage the clicks, the tracker and the rubber band displayed on the histogram.
     */
	class HistogramPicker : public QwtPlotPicker
	{
		Q_OBJECT
	private:
		virtual QwtText trackerTextF(const QPointF& point) const;		
		
	public:
		/*!
		 * \brief Default constructor
		 * 
		 * Construct a basic QwtPlotCanvas without tracker and rubber band
		 * 
		 * \param canvas The QwtPlotCanvas to supervise
		 */
		HistogramPicker(QwtPlotCanvas* canvas);
		
		/*!
		 * \brief Default constructor
		 * 
		 * Construct a QwtPlotCanvas with tracker and rubber band
		 * 
		 * \param rubberBand The rubber band style
		 * \param trackerMode The tracker's display mode
		 * \param canvas The QwtPlotCanvas to supervise
		 */
		HistogramPicker(RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas* canvas);
	
		
	signals:
		/*!
		 * \brief Signal emit when the mouse move over the picker
		 * 
		 * \param pos The mouse position
		 */
		void moved(const QPointF& pos) const;
	};
}

#endif //HISTOGRAMPICKER_H
