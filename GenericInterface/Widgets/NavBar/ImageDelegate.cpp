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

#include "ImageDelegate.h"

#include <iostream>

using namespace genericinterface;

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QRect rect = option.rect;
  rect.adjust(3, 3, -3, -3);
  
  if (option.state & QStyle::State_Selected)
    painter->fillRect(option.rect, option.palette.highlight());

  QImage img(index.data().toString());

  if (img.width() > img.height())
  {
    double scale = (double)rect.width() / (double)img.width();
    int size = (int) ((double)img.height() * scale);
    int adjust = (rect.height() - size) / 2;
    rect.adjust(0, adjust, 0, -adjust);
  }
  else if (img.height() > img.width()) 
  {
    double scale = (double)rect.width() / (double)img.height();
    int size = (int) ((double)img.width() * scale);
    //int adjust = size / 2;
    int adjust = (rect.width() - size) / 2;
    rect.adjust(adjust, 0, -adjust, 0);
  }

  painter->drawImage(rect, img);
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  return QSize(75,75);
}
