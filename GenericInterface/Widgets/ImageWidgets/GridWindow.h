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
    GridWindow(QString & path, ImageWindow* source = 0);

    virtual AlternativeImageView* getView() { return NULL; }
  protected:
    GridView* _view; /*!< the widget which deals with the pixels display */
  };
}

#endif
