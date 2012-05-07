#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <iostream>
#include <sstream>

#include <Rectangle.h>

#include "AlternativeImageView.h"

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
    imagein::Rectangle* _applicationArea;
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
    ImageWindow(const QString & path, const ImageWindow* source = 0, imagein::Rectangle* rect = 0);

    QString& getPath();
    static std::string getTitleFromPath(const QString& path);
    
    virtual AlternativeImageView* getView()=0;
      
  public slots:
    void activated();
    void setApplicationArea(const imagein::Rectangle* rect);
	
	signals:
		/*!
		 * \brief Signal emits when this is activated
		 * 
		 * \param rect Rectangle to display on the source window
		 */
		void highlightRectChange(const imagein::Rectangle* rect, ImageWindow* source);
  };
}

#endif // IMAGEWINDOW_H
