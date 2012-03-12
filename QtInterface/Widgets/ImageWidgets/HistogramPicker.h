#ifndef HISTOGRAMPICKER_H
#define HISTOGRAMPICKER_H

#include <QPainter>

#include <qwt_plot.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_canvas.h>

namespace genericinterface
{
	class HistogramPicker : public QwtPlotPicker
	{
		Q_OBJECT
		
	public:
		HistogramPicker(QwtPlotCanvas* canvas);
		HistogramPicker(RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas* canvas);
	
		virtual QwtText trackerTextF(const QPointF& point) const;
		
	signals:
		void moved(const QPointF& pos) const;
	};
}

#endif //HISTOGRAMPICKER_H
