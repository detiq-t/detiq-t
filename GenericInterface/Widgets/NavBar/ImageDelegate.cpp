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
    int adjust = - size / 2;
    rect.adjust(0, adjust, 0, -adjust);
  }
  else if (img.height() > img.width()) 
  {
    double scale = (double)rect.height() / (double)img.height();
    int size = (int) ((double)img.width() * scale);
    int adjust = size / 2;
    rect.adjust(adjust, 0, -adjust, 0);
  }

  painter->drawImage(rect/*QRectF(30, index.row()*100, 50, 50)*/, img);
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  return QSize(75,75);
}
