#include "RowView.h"

using namespace genericinterface;
using namespace imagein;

RowView::RowView(const Image* image, const Rectangle* rect): GenericHistogramView(image, rect)
{
	_qwtPlot->setTitle("Profile Histogram");
}
