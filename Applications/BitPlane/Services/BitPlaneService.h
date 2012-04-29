#ifndef BITPLANESERVICE_H
#define BITPLANESERVICE_H

#include <Services/AlgorithmService.h>
#include "../Widgets/BitPlaneChoice.h"
#include <Image.h>

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
    void apply(imagein::algorithm::BitPlane<imagein::Image>* bitplanealgo);

  private:
    QAction* _bitplane;
    BitPlaneChoice* _bitplanechoice;
  };
}

#endif
