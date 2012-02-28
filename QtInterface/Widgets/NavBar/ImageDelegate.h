#ifndef QTINTERFACE_WIDGET_IMAGEDELEGATE_H
#define QTINTERFACE_WIDGET_IMAGEDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
#include <QRectF>

class ImageDelegate : public QItemDelegate
{
 void paint(QPainter *painter, const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
  {
    QRect rect = option.rect;
    rect.adjust(5, 5, -5, -5);
    
    if (option.state & QStyle::State_Selected)
      painter->fillRect(option.rect, option.palette.highlight());

    painter->drawImage(rect/*QRectF(30, index.row()*100, 50, 50)*/, QImage(index.data().toString()));
  }

  QSize sizeHint (const QStyleOptionViewItem & option, const QModelIndex & index) const
  {
    return QSize(75,75);
  }
};

#endif
