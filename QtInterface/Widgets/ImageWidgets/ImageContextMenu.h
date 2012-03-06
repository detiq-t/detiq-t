#ifndef IMAGECONTEXTMENU_H
#define IMAGECONTEXTMENU_H

#include <QMenu>
#include <QMouseEvent>
#include <QPoint>
#include <iostream>

namespace genericinterface
{
    class ImageContextMenu : public QMenu
    {
		Q_OBJECT
	public:
		ImageContextMenu(QWidget* parent=NULL);
        
    public slots:
		void showContextMenu(const QPoint& pos);
    };
}

#endif // IMAGECONTEXTMENU_H
