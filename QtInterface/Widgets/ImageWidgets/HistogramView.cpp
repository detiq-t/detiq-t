#include "HistogramView.h"

using namespace genericinterface;
using namespace imagein;

HistogramView::HistogramView(const Image* image, const imagein::Rectangle* rect): GenericHistogramView(image, rect)
{
	_qwtPlot->setTitle("Histogram");
}

    
