#ifndef ROWVIEW_H
#define ROWVIEW_H

#include <QScrollArea>
#include <QMouseEvent>

#include <qpen.h>
#include <qwt_plot.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_picker_machine.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <stdlib.h>

#include <Image.h>
#include <Rectangle.h>
#include <Histogram.h>

#include "HistogramPicker.h"
#include "GraphicalHistogram.h"
#include "AlternativeImageView.h"

namespace genericinterface
{
    class RowView : public AlternativeImageView
    {
		Q_OBJECT
	private:
		imagein::Rectangle* _rectangle;
		QwtPlot* _qwtPlot;
		HistogramPicker* _principalPicker;
		HistogramPicker* _leftPicker;
		HistogramPicker* _rightPicker;
        
		void init();
		void populate();

    public:
		RowView(imagein::Image* image, imagein::Rectangle* rect);
        imagein::Histogram* getHistogram(int channel) const;
        QwtPlot* getGraphicalHistogram() const;
		
	signals:
		void leftClickedValue(int value);
		void rightClickedValue(int value);
		void hoveredValue(int value) const;
		
	private Q_SLOTS:
		void showItem(QwtPlotItem*, bool on);
		void move(const QPointF&) const;
		void leftClick(const QPointF&);
		void rightClick(const QPointF&);
    };
}

#endif // ROWVIEW_H
