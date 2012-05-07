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

