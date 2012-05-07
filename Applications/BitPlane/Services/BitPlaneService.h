#ifndef BITPLANESERVICE_H
#define BITPLANESERVICE_H

#include <GenericInterface.h>
#include <Services/AlgorithmService.h>
#include "../Widgets/BitPlaneWindow.h"

using namespace bitplane;

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
    BitPlaneWindow* _bitplanewindow;
  };
}

#endif
