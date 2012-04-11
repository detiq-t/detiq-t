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
