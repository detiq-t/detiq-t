#ifndef STANDARDIMAGEWINDOW_H
#define STANDARDIMAGEWINDOW_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QScrollArea>
#include <QFont>
#include <QKeyEvent>
#include <QPoint>
#include <QInputDialog>

#include <sstream>
#include <iostream>
#include <list>

#include "ImageWindow.h"
#include "RowWindow.h"
#include "HistogramWindow.h"
#include "ProjectionHistogramWindow.h"
#include "StandardImageView.h"

#include "../../GenericInterface.h"

#include <Image.h>
#include <Rectangle.h>
#include <Histogram.h>

#include <QString>

namespace genericinterface
{
	/*!
     * \brief Contains the StandardImageWindow
     *
     * Creates and display the StandardImageWindow, and update the status bar.
     */
    class StandardImageWindow : public ImageWindow
    {
		Q_OBJECT
    private:
        GenericInterface* _gi;

        //QMdiArea* _area;
		imagein::Image* _image;
        StandardImageView* _imageView;
        QLabel* _lImageSize;
        QLabel* _lImageName;
        QLabel* _lHoveredPixelInfo;
        QLabel* _lHoveredPixelPosition;
        QLabel* _lHoveredPixelColor;
        QLabel* _lSelectedPixelInfo;
        QLabel* _lSelectedPixelPosition;
        QLabel* _lSelectedPixelColor;
        QLabel* _lZoom;
        QPoint* _selectedPixel;
        bool _isRootImage;

        void init();
        void initStatusBar();
        std::list<HistogramWindow*> getHistogram();
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);
   
    protected:
	     void closeEvent(QCloseEvent* event);

    public slots:
        void showHistogram();
        void showHProjectionHistogram();
        void showVProjectionHistogram();
        void showPixelsGrid();
        void showLineProfile();
        void showColumnProfile();
        
        void showHoveredPixelInformations(int x, int y) const;
        void showSelectedPixelInformations(int x, int y) const;
        void updateZoom(double z) const;
        
        void showHighlightRect(const imagein::Rectangle* rect);
        
	signals:
		//! Signal emits when crtl key is pressed
		void ctrlPressed();
		
		/*!
		 * \brief Signal emits when the highlight rect have to changes
		 * 
		 * \param rect The rectangle to display
		 */
		void highlightRectChange(const imagein::Rectangle* rect);    

    public:
		/*!
		 * \brief Default constructor
		 * 
		 * Display StandardImageWindow with StandardImageView from image path.
		 * 
		 * \param path The image path
		 * \param gi The interface associated with this
		 */
        StandardImageWindow(const QString & path, GenericInterface* gi);
        
		/*!
		 * \brief StandardImageWindow destructor.
		 *
		 * The StandardImageView is deleted too.
		 */
		virtual ~StandardImageWindow();
        
        //! Set the view as root
		inline void setAsRoot() { _isRootImage = true; }
    };
}

#endif // STANDARDIMAGEWINDOW_H
