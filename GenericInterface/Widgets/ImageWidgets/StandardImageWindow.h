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

#ifndef STANDARDIMAGEWINDOW_H
#define STANDARDIMAGEWINDOW_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QFont>
#include <QKeyEvent>
#include <QPoint>
#include <QInputDialog>

#include <sstream>
#include <iostream>
#include <list>

#include "ImageWindow.h"
#include "RowWindow.h"
#include "HistogramWindow.h"
#include "ProjectionHistogramWindow.h"
#include "StandardImageView.h"
#include "AlternativeImageView.h"
#include "GridWindow.h"
#include "GraphicalHistogram.h"

#include "../../GenericInterface.h"

#include <Image.h>
#include <Rectangle.h>
#include <Histogram.h>


namespace genericinterface
{
/*!
 * \brief Contains the StandardImageWindow
 *
 * Creates and display the StandardImageWindow, and update the status bar.
 */
class StandardImageWindow : public ImageWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Default constructor
     *
     * Display StandardImageWindow with StandardImageView from image path.
     *
     * \param path The image path
     * \param gi The interface associated with this
     */
    StandardImageWindow(const QString path, GenericInterface* gi);

    /*!
     * \brief Constructor based on an Image already openned
     *
     * Display StandardImageWindow with StandardImageView from image path.
     *
     * \param path The image path (to attach to the right set)
     * \param gi The interface associated with this
     * \param image The image which is used
     */
    StandardImageWindow(const QString path, GenericInterface* gi, Image* image);


    /*!
     * \brief StandardImageWindow destructor.
     *
     * The StandardImageView is deleted too.
     */
    virtual ~StandardImageWindow();

    /*!
     * \brief Returns the Image contained in the window.
     *
     */
    const imagein::Image* getImage();

    /*!
     * \brief Changes the Image contained in the window.
     *
     * \param image The image we want to put in the window.
     */
    void setImage(Image* image);

    /*!
     * \brief Returns the Rectangle which is the current image's selection on the window.
     *
     */
    const imagein::Rectangle* getSelection();

    inline StandardImageView* getStandardView() { return _imageView; }


    AlternativeImageView* getView() { return NULL; }


public slots:
    void showHistogram();
    void showHProjectionHistogram();
    void showVProjectionHistogram();
    void showPixelsGrid();
    void showLineProfile();
    void showColumnProfile();
    
    void showHoveredPixelInformations(int x, int y) const;
    void showSelectedPixelInformations(int x, int y) const;
    void updateZoom(double z) const;
    
    void showHighlightRect(const imagein::Rectangle* rect, ImageWindow* source);

signals:
    //! Signal emits when crtl key is pressed
    void ctrlPressed();

    /*!
     * \brief Signal emits when the highlight rect have to changes
     *
     * \param rect The rectangle to display
     */
    void highlightRectChange(const imagein::Rectangle* rect, ImageWindow* source);
    
protected:
    GenericInterface* _gi;
    imagein::Image* _image;
    StandardImageView* _imageView;
    QLabel* _lImageSize;
    QLabel* _lImageName;
    QLabel* _lHoveredPixelInfo;
    QLabel* _lHoveredPixelPosition;
    QLabel* _lHoveredPixelColor;
    QLabel* _lSelectedPixelInfo;
    QLabel* _lSelectedPixelPosition;
    QLabel* _lSelectedPixelColor;
    QLabel* _lZoom;
    QPoint* _selectedPixel;

    void init();
    void initStatusBar();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
};
}

#endif // STANDARDIMAGEWINDOW_H
