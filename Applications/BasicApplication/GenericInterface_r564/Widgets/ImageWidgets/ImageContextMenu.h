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
