/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HISTOGRAMWINDOW_H
#define HISTOGRAMWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFont>
#include <sstream>

#include "ImageWindow.h"
#include "HistogramView.h"

#include <Image.h>
#include <Rectangle.h>
#include <Histogram.h>

namespace genericinterface
{
	/*!
     * \brief Contains the HistogramView
     *
     * Creates and display the HistogramView, and update the status bar.
     */
    class HistogramWindow : public ImageWindow
    {
		Q_OBJECT
    private:
        HistogramView* _view;
        QLabel* _lImageName;
        QLabel* _lHoveredValue;
        QLabel* _lSelectedValue1;
        QLabel* _lSelectedValue2;
		
		void init();
        void initStatusBar();
        QString valueFromHistogram(unsigned int value) const;
        
    public slots:
        void showHoveredValue(int value) const;
        void showLeftClickedValue(int value) const;
        void showRightClickedValue(int value) const;
        
    public:
      /*!
       * \brief Default constructor
       * 
       * Initializes and display the HistogramView from the parameters. 
       * 
       * \param image The image concerned by the histogram
       * \param rect The part of the image where the histogram is applied
       * \param source The ImageWindow source (window which contains the image)
       */
      HistogramWindow(QString path, const imagein::Image* image, imagein::Rectangle* rect, const ImageWindow* source);
        
      /*!
       * \brief HistogramWindow destructor.
       *
       * The HistogramView is deleted too
       */
      virtual ~HistogramWindow();
      
      virtual AlternativeImageView* getView() { return _view; }
    };
}

#endif // HISTOGRAMWINDOW_H
