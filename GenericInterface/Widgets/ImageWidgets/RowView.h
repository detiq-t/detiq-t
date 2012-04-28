#ifndef ROWVIEW_H
#define ROWVIEW_H

#include "GenericHistogramView.h"

namespace genericinterface
{
	/*!
     * \brief Create and display a graphical row or column profile
     *
     * Creates and display a graphical row or column profile from an image and a line.
     * This class manages via HistogramPicker the mouse events.
     */
    class RowView : public GenericHistogramView
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
		RowView(const imagein::Image* image, imagein::Rectangle* rect);
    };
}

#endif // ROWVIEW_H
