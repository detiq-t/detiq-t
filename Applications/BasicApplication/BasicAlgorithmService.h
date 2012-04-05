#ifndef BASICALGORITHMSERVICE_H
#define BASICALGORITHMSERVICE_H

#include <Services/AlgorithmService.h>

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
