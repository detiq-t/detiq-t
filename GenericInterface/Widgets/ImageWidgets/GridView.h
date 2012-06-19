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

#ifndef WIDGET_ZOOMWIDGET_H
#define WIDGET_ZOOMWIDGET_H

#include <QRadioButton>

#include <Image.h>
#include "../ImageWidgets/AlternativeImageView.h"

class QHBoxLayout;


namespace genericinterface
{
  class ChannelSelector : public QRadioButton
  {
  Q_OBJECT
  public:
      ChannelSelector(const QString& name, int nb);
  signals:
      void activated(int);
  public slots:
      void send(bool);
  private:
      int _nb;
  };

  class RadioPanel : public QWidget
  {
  Q_OBJECT
  public:
      RadioPanel(int nb = 1);
  signals:
      void activated(int);

  private slots:
      void rcvActivated(int);
  };

  class ImageViewer;

  /**
  * @brief The grid view manages the interaction of the users with the grid
  * pixel. It deals with the events of the mouse and
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
    GridView(const imagein::Image* im, int dx, int dy);

  private:
    QHBoxLayout* _layout; /*!< the layout of the widget */
    ImageViewer* _viewer; /*!< the viewer which permits to see the complete picture */
  };
}

#endif
