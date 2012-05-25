#ifndef WIDGET_ZOOMWIDGET_H
#define WIDGET_ZOOMWIDGET_H

#include <Image.h>
#include "../ImageWidgets/AlternativeImageView.h"

class QHBoxLayout;

namespace genericinterface
{
  class ImageViewer;

  /**
  * @brief The grid view manages the interaction of the users with the grid pixel. It deals with the events of the mouse and
  * the keyboard
  */
  class GridView : public AlternativeImageView
  {
  public:
    /**
    * @brief The constructor of the class
    *
    * Be careful, in this case, the origin is the top left of the screen
    *
    * @param im the image which has to be displayed
    * @param path the path of the origin file
    * @param dx the original horizontal offset
    * @param dy the original vertical offset
    */
    GridView(imagein::Image* im, const QString & path, int dx, int dy);

  private:
    QHBoxLayout* _layout; /*!< the layout of the widget */
    ImageViewer* _viewer; /*!< the viewer which permits to see the complete picture */
  };
}

#endif
