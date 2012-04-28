#ifndef PROJECTIONHISTOGRAMVIEW_H
#define PROJECTIONHISTOGRAMVIEW_H

#include <Image.h>
#include <Rectangle.h>
#include <ProjectionHistogram.h>

#include "GenericHistogramView.h"

namespace genericinterface
{
	/*!
     * \brief Create and display a graphical projection histogram
     *
     * Creates and display a projection histogram from an image and a rectangle.
     * This class manages via HistogramPicker the mouse events.
     */
    class ProjectionHistogramView : public GenericHistogramView
    {
		Q_OBJECT
	
    public:
		/*!
		 * \brief Default constructor
		 * 
		 * Initializes and display the histogram from the parameters. 
		 * 
		 * \param image The image concerned by the histogram
		 * \param rect The part of the image where the histogram is applied
		 */
		ProjectionHistogramView(const imagein::Image* image, imagein::Rectangle* rect, int value, bool horizontal);
        
        //! Returns true if it's horizontal, else false
        inline bool isHorizontal() const { return _horizontal; }
		
	private slots:
		void showItem(QwtPlotItem*, bool on) const;
		void move(const QPointF&) const;
		void leftClick(const QPointF&) const;
		void rightClick(const QPointF&) const;
    };
}

#endif // PROJECTIONHISTOGRAMVIEW_H

