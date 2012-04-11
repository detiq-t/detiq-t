#include "ImageDelegate.h"

using namespace genericinterface;

void ImageDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  QRect rect = option.rect;
  rect.adjust(5, 5, -5, -5);
  
  if (option.state & QStyle::State_Selected)
    painter->fillRect(option.rect, option.palette.highlight());
	 
  painter->drawImage(rect/*QRectF(30, index.row()*100, 50, 50)*/, QImage(index.data().toString()));
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
  return QSize(75,75);
}
