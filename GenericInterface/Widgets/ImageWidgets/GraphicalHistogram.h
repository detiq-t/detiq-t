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
