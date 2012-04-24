#ifndef BINARIZATIONSERVICE_H
#define BINARIZATIONSERVICE_H

#include <Services/AlgorithmService.h>

#include <QToolBar>

namespace genericinterface
{
  /*!
   * \brief 
	*
	* 
	*/
  class BinarizationService : public AlgorithmService
  {
  Q_OBJECT
  public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

  public slots:
	 void applyOtsu();
	 void applyManualBinarization();

  private:
    QToolBar* _toolBar;
	 QAction* _otsu;
	 QAction* _manual;
  };
}

#endif
