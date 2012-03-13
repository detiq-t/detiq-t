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
	/*!
     * \brief Create and display a graphical row or column profile
     *
     * Creates and display a graphical row or column profile from an image and a line.
     * This class manages via HistogramPicker the mouse events.
     */
    class RowView : public AlternativeImageView
    {
		Q_OBJECT
	private:
		const imagein::Rectangle* _rectangle;
		QwtPlot* _qwtPlot;
		HistogramPicker* _principalPicker;
		HistogramPicker* _leftPicker;
		HistogramPicker* _rightPicker;
        
		void init();
		void populate();

    public:
		/*!
		 * \brief Default constructor
		 * 
		 * Initializes and display the histogram from the parameters. 
		 * 
		 * \param image The image concerned by the histogram
		 * \param rect The part of the image where the histogram is applied
		 */
		RowView(const imagein::Image* image, const imagein::Rectangle* rect);
		
		//! Returns the image's histogram on the param channel
        inline const imagein::Histogram* getHistogram(int channel) const { return new imagein::Histogram(*_image, channel, *_rectangle); }
        
		//! Returns the graphical histogram
        inline QwtPlot* getGraphicalHistogram() const { return _qwtPlot; }
		
	signals:
		/*!
		 * \brief Signal emits when the mouse left button is clicked
		 * 
		 * \param value Value selected
		 */
		void leftClickedValue(int value) const;
		
		/*!
		 * \brief Signal emits when the mouse right button is clicked
		 * 
		 * \param value Value selected
		 */
		void rightClickedValue(int value) const;
		
		/*!
		 * \brief Signal emits when the mouse move over the histogram
		 * 
		 * \param value Value hovered
		 */
		void hoveredValue(int value) const;
		
	private slots:
		void showItem(QwtPlotItem*, bool on) const;
		void move(const QPointF&) const;
		void leftClick(const QPointF&) const;
		void rightClick(const QPointF&) const;
    };
}

#endif // ROWVIEW_H
