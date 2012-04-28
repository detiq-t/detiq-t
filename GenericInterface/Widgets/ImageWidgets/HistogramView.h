#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include "GenericHistogramView.h"

namespace genericinterface
{
	/*!
     * \brief Create and display a graphical histogram
     *
     * Creates and display a graphical histogram from an image and a rectangle.
     * This class manages via HistogramPicker the mouse events.
     */
    class HistogramView : public GenericHistogramView
    {	
    public:
		/*!
		 * \brief Default constructor
		 * 
		 * Initializes and display the histogram from the parameters. 
		 * 
		 * \param image The image concerned by the histogram
		 * \param rect The part of the image where the histogram is applied
		 */
		HistogramView(const imagein::Image* image, imagein::Rectangle* rect);
    };
}

#endif // HISTOGRAMVIEW_H
