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

#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <iostream>
#include <sstream>

#include <Rectangle.h>

#include "AlternativeImageView.h"

namespace genericinterface
{
/*!
   * \brief Inherited class by all Windows
   *
   * The ImageWindow class contains the status bar and inherit QWidget.
   */
class ImageWindow : public QWidget
{
        Q_OBJECT
    protected:
        imagein::Rectangle* _applicationArea;
        QStatusBar* _statusBar;
        const ImageWindow* _sourceWindow;
        QString _path;

    public:
        ImageWindow(QString path);
        /*!
         * \brief Default constructor.
         *
         * Constructs an empty QWidget and initialized the source window and the application area from parameters.
         *
         * \param source The source window
         * \param rect The application area (Rectangle used for Histogram, Algorithm...)
         */
        ImageWindow(QString path, const ImageWindow *source, Rectangle *rect = 0);

        /*!
         * \brief Returns the title from a path.
         *
         * \param path The path of a file.
         */
        static QString getTitleFromPath(QString path);

        QString getPath(){ return _path; }

        QString getName(){ return getTitleFromPath(_path); }

        /*!
         * \brief Returns the view in the window.
         *
         */
        virtual AlternativeImageView* getView()=0;

    public slots:
        void activated();
        void setApplicationArea(const imagein::Rectangle* rect);

    signals:
        /*!
         * \brief Signal emits when this is activated
         *
         * \param rect Rectangle to display on the source window
         */
        void highlightRectChange(const imagein::Rectangle* rect, ImageWindow* source);
    };
}

#endif // IMAGEWINDOW_H
