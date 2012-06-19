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

#ifndef IMAGECONTEXTMENU_H
#define IMAGECONTEXTMENU_H

#include <QMenu>
#include <QMouseEvent>
#include <QPoint>
#include <iostream>

namespace genericinterface
{
	/*!
     * \brief Popup menu on StandardImageView
     *
     * Display a popup menu on each StandardImageView
     */
    class ImageContextMenu : public QMenu
    {
		Q_OBJECT
	public:
		/*!
		 * \brief Default constructor
		 * 
		 * Creates a basic QWidget.
		 * 
		 * \param parent The parent widget
		 */
		ImageContextMenu(QWidget* parent=NULL);
        
    public slots:
		/*!
		 * \brief Display the popup menu
		 * 
		 * \param pos The point where display it
		 */
		void showContextMenu(const QPoint& pos);
    };
}

#endif // IMAGECONTEXTMENU_H
