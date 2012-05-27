#ifndef PROJECTIONHISTOGRAMWINDOW_H
#define PROJECTIONHISTOGRAMWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QFont>
#include <sstream>

#include "ImageWindow.h"
#include "ProjectionHistogramView.h"

#include <Image.h>
#include <Rectangle.h>
#include <Histogram.h>

namespace genericinterface
{
	/*!
   * \brief Contains the ProjectionHistogramView
   *
   * Creates and display the ProjectionHistogramView, and update the status bar.
   */
  class ProjectionHistogramWindow : public ImageWindow
  {
  Q_OBJECT
  private:
    ProjectionHistogramView* _view;
    QLabel* _lImageName;
    QLabel* _lHoveredValue;
    QLabel* _lSelectedValue1;
    QLabel* _lSelectedValue2;
		
		void init();
    void initStatusBar();
    QString valueFromHistogram(unsigned int value) const;
        
  public slots:
    void showHoveredValue(int value) const;
    void showLeftClickedValue(int value) const;
    void showRightClickedValue(int value) const;
        
  public:
		/*!
		 * \brief Default constructor
		 * 
		 * Initializes and display the HistogramView from the parameters. 
		 * 
		 * \param image The image concerned by the histogram
		 * \param rect The part of the image where the histogram is applied
		 * \param source The ImageWindow source (window which contains the image)
		 */
    ProjectionHistogramWindow(const QString path, const imagein::Image* image, imagein::Rectangle* rect, const ImageWindow* source, int value, bool horizontal=true);
        
		/*!
		 * \brief ProjectionHistogramWindow destructor.
		 *
		 * The ProjectionHistogramView is deleted too
		 */
		virtual ~ProjectionHistogramWindow();
    
    virtual AlternativeImageView* getView() { return _view; }
  };
}

#endif // PROJECTIONHISTOGRAMWINDOW_H

