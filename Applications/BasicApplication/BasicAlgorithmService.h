#ifndef BASICALGORITHMSERVICE_H
#define BASICALGORITHMSERVICE_H

#include "GenericInterface_r564/Services/AlgorithmService.h"
#include "GenericInterface_r564/Widgets/ImageWidgets/StandardImageWindow.h"

namespace genericinterface
{
  /*!
   * \brief First implementation of AlgorithlService with basic algorithms
	*
	* It contains the algorithm Identity and Inversion
	*/
  class BasicAlgorithmService : public AlgorithmService
  {
  Q_OBJECT
  public:
    void connect(GenericInterface* gi);
    void display(GenericInterface* gi);

  public slots:
    void applyIdentity();
    void applyInversion();
	 //void applyAverage();

  signals:
    void newImageWindowCreated(const QString& path, ImageWindow* widget);

  private:
    QAction* _identity;
    QAction* _inversion;
    //QAction* _average;
  };
}

#endif
