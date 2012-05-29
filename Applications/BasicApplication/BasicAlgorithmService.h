#ifndef BASICALGORITHMSERVICE_H
#define BASICALGORITHMSERVICE_H

#include <Services/AlgorithmService.h>

#include <QToolBar>

namespace genericinterface
{
  /*!
   * \brief First implementation of AlgorithmService with basic algorithms
	*
	* It contains the algorithm Identity and Inversion
	*/
  class BasicAlgorithmService : public AlgorithmService
  {
  Q_OBJECT
  public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

  public slots:
    void applyIdentity();
    void applyInversion();

  private:
    QAction* _identity;
    QAction* _inversion;
  };
}

#endif
