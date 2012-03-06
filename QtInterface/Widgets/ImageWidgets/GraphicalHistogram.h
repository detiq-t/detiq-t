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
	class GraphicalHistogram: public QwtPlotHistogram
	{
	public:
		GraphicalHistogram(const QString& title, const QColor& color);

		void setColor(const QColor& color);
		void setValues(int numValues, int* values);
	};
}

#endif // GRAPHICALHISTOGRAM_H
