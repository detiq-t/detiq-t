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

#ifndef QTINTERFACE_WIDGET_IMAGEDELEGATE_H
#define QTINTERFACE_WIDGET_IMAGEDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
#include <QRectF>

namespace genericinterface
{
  class ImageDelegate : public QItemDelegate
  {
    /**
	 * @brief Redefinition of paint() from QItemDelegate to change de display in the navigation bar.
	 //TODO parameters
	 * @param painter xxx
	 * @param option xxx
	 * @param index xxx
	 */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
    /**
	 * @brief Redefinition of sizeHint) from QItemDelegate.
	 //TODO parameters
	 * @param option xxx
	 * @param index xxx
	 */
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
  };
}

#endif
