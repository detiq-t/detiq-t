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

#ifndef GRAPHICALHISTOGRAM_H
#define GRAPHICALHISTOGRAM_H

#include <QString>
#include <QColor>
#include <QPen>
#include <QPalette>

#include <qwt_plot_histogram.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>

namespace genericinterface
{
	/*!
     * \brief Create graphical histogram from values
     *
     * This class is used to create graphical histogram from values and color
     */
	class GraphicalHistogram: public QwtPlotHistogram
	{
	public:    
		/*!
		 * \brief Default constructor.
		 * 
		 * Constructs an empty QwtPlotHistogram.
		 *
		 * \param title The histogram's title
		 * \param color The color of the columns
		 */
		GraphicalHistogram(const QString& title, const QColor& color);

		/*!
		 * \brief Set the histogram's values
		 *
		 * \param numValues Values number
		 * \param values Table of values
		 */
		void setValues(int numValues, int* values);
	};
}

#endif // GRAPHICALHISTOGRAM_H
