#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <iostream>

#include <Rectangle.h>

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
        const imagein::Rectangle* _applicationArea;
        QStatusBar* _statusBar;
        const ImageWindow* _sourceWindow;
        QString _path; /*!< The path of the source image */

    public:
		/*!
		* \brief Default constructor.
		* 
		* Constructs an empty QWidget and initialized the source window and the application area from parameters.
		*
		* \param source The source window
		* \param rect The application area (Rectangle used for Histogram, Algorithm...)
		*/
        ImageWindow(const ImageWindow* source = 0, const imagein::Rectangle* rect = 0);
        
    public slots:
        void activated();
	
	signals:
		/*!
		 * \brief Signal emits when this is activated
		 * 
		 * \param rect Rectangle to display on the source window
		 */
		void highlightRectChange(const imagein::Rectangle* rect);
    };
}

#endif // IMAGEWINDOW_H
