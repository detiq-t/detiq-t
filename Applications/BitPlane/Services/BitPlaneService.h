#ifndef BITPLANESERVICE_H
#define BITPLANESERVICE_H

#include <Services/AlgorithmService.h>

namespace genericinterface
{
  class BitPlaneService : public AlgorithmService
  {
  Q_OBJECT
  public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

  public slots:
    void applyBitPlane();

  private:
    QAction* _bitplane;
  };
}

#endif
