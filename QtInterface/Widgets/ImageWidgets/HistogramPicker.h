#ifndef HISTOGRAMPICKER_H
#define HISTOGRAMPICKER_H

#include <QPainter>

#include <qwt_plot.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_canvas.h>

namespace genericinterface
{
	/*!
     * \brief Management of mouse events on a histogram
     * 
     * A special object inherit from QwtPlotPicker is required to manage mouse events.
     * This class manage the clicks, the tracker and the rubber band displayed on the histogram.
     */
	class HistogramPicker : public QwtPlotPicker
	{
		Q_OBJECT
	private:
		virtual QwtText trackerTextF(const QPointF& point) const;		
		
	public:
		/*!
		 * \brief Default constructor
		 * 
		 * Construct a basic QwtPlotCanvas without tracker and rubber band
		 * 
		 * \param canvas The QwtPlotCanvas to supervise
		 */
		HistogramPicker(QwtPlotCanvas* canvas);
		
		/*!
		 * \brief Default constructor
		 * 
		 * Construct a QwtPlotCanvas with tracker and rubber band
		 * 
		 * \param rubberBand The rubber band style
		 * \param trackerMode The tracker's display mode
		 * \param canvas The QwtPlotCanvas to supervise
		 */
		HistogramPicker(RubberBand rubberBand, DisplayMode trackerMode, QwtPlotCanvas* canvas);
	
		
	signals:
		/*!
		 * \brief Signal emit when the mouse move over the picker
		 * 
		 * \param pos The mouse position
		 */
		void moved(const QPointF& pos) const;
	};
}

#endif //HISTOGRAMPICKER_H
