#ifndef ROWVIEW_H
#define ROWVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QMouseEvent>

#include <qpen.h>
#include <qwt_plot.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_histogram.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>

#include "GraphicalHistogram.h"
#include "AlternativeImageView.h"

#include <Image.h>

namespace genericinterface
{
    class RowView : public AlternativeImageView
    {
		Q_OBJECT
	private:
		imagein::Histogram* _histogram;
		QwtPlot* _qwtPlot;
        
		void init();
		void populate();
        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);

    public:
		RowView(imagein::Image* image, imagein::Histogram* histogram);
        QwtPlot* getHistogram();
		
	signals:
		void valueClickedLeft(int value);
		void valueClickedRight(int value);
		void valueHovered(int value);
    };
}

#endif // ROWVIEW_H
