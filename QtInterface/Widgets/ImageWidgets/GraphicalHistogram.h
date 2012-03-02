#ifndef GRAPHICALHISTOGRAM_H
#define GRAPHICALHISTOGRAM_H

#include <QString>
#include <QColor>

#include <qwt_plot_histogram.h>
#include <qwt_series_data.h>

namespace genericinterface
{
	class GraphicalHistogram: public QwtPlotHistogram
	{
	public:
		GraphicalHistogram(const QString &, const QColor &);

		void setColor(const QColor &);
		void setValues(int numValues, int* values);
	};
}

#endif // GRAPHICALHISTOGRAM_H
