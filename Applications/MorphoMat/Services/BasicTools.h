#ifndef BASICTOOLS_H
#define BASICTOOLS_H

#include <Service.h>
#include <QMenu>

namespace genericinterface
{
  /*!
   * \brief 
	*
	* 
	*/
  class BasicTools : public QObject, public Service
  {
  Q_OBJECT
  public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

  public slots:
    void applyIdentity();
    void applyInversion();
	 void convertToGrayscale(); // call an algorithm to transform to a grayscale image

  private:
    QMenu* _menu;
    QAction* _identity;
    QAction* _inversion;
	 QAction* _convertToGrayscale;
  };
}

#endif
