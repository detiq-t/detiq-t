#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QScrollArea>
#include <QMouseEvent>

#include <qpen.h>
#include <qwt_plot.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_histogram.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <stdlib.h>

#include <Image.h>
#include <Rectangle.h>
#include <Histogram.h>

#include "GraphicalHistogram.h"
#include "AlternativeImageView.h"

namespace genericinterface
{
    class HistogramView : public AlternativeImageView
    {
		Q_OBJECT
	private:
		imagein::Rectangle* _rectangle;
		QwtPlot* _qwtPlot;
		QwtPlotPicker* _qwtLeftPicker;
		QwtPlotPicker* _qwtRightPicker;
		
		void init();
		void populate();
		//QwtText trackerText(const QPoint& pos) const;
	
    public:
		HistogramView(imagein::Image* image, imagein::Rectangle* rect);
        int getMemorisedValue(int i);
        void setMemorisedValue(int i, int value);
        QwtPlot* getHistogram();
		
	signals:
		void leftClickedValue(int value);
		void rightClickedValue(int value);
		void hoveredValue(int value);
		
	private Q_SLOTS:
		void showItem(QwtPlotItem*, bool on);
		void leftClick(const QPointF&);
		void rightClick(const QPointF&);
    };
}

#endif // HISTOGRAMVIEW_H
