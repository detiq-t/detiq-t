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

#ifndef WIDGET_GRIDWINDOW_H
#define WIDGET_GRIDWINDOW_H

#include "../ImageWidgets/ImageWindow.h"

/**
* @brief Vizualisation of pixels' grid
*/

namespace genericinterface
{
  class GridView;

  /**
  * @brief This widget displays the image with an important zoom, so each pixel can be
  * seen quickly.
  *
  * It helps the user to understand what a pixel is: a simple square of color.
  * The values of channels are displaying too, directly on the square
  */
  class GridWindow : public ImageWindow
  {
  public:
    /**
    * @brief The constructor of the class
    *
    * @param path the path of the image's file
    * @param source the widget which asked for the creation of the grid
    * @param rect the original view
    */
    GridWindow(const QString& path, const imagein::Image* img, ImageWindow* source = 0);

    virtual AlternativeImageView* getView() { return NULL; }
  protected:
    GridView* _view; /*!< the widget which deals with the pixels display */
  };
}

#endif
