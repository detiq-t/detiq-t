#ifndef ROWWINDOW_H
#define ROWWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

#include <sstream>

#include "ImageWindow.h"
#include "RowView.h"

#include "../../GenericInterface.h"

#include <Image.h>

namespace genericinterface
{
	/*!
   * \brief Contains the RowView
   *
   * Creates and display the RowView, and update the status bar.
   */
  class RowWindow : public ImageWindow
  {
  Q_OBJECT
  private:
    RowView* _view;
    QLabel* _lImageName;
    QLabel* _lHoveredValue;
    QLabel* _lSelectedValue1;
    QLabel* _lSelectedValue2;
    GenericInterface* _gi;
		
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
		 * Initializes and display the RowView from the parameters. 
		 * 
		 * \param image The image concerned by the histogram
		 * \param rect The part of the image where the histogram is applied
		 * \param path The path of the image
		 * \param gi The interface associated to him
		 * \param source The ImageWindow source (window which contains the image)
		 * \param vertical False : row profile ; True : column profile
		 */
    RowWindow(const imagein::Image* image, imagein::Rectangle* rect, const QString path, GenericInterface *gi, const ImageWindow* source, bool vertical=false);
    
		
		/*!
		 * \brief RowWindow destructor.
		 *
		 * The RowView is deleted too
		 */
		virtual ~RowWindow();
    
    virtual AlternativeImageView* getView() { return _view; }
  };
}

#endif // ROWWINDOW_H
