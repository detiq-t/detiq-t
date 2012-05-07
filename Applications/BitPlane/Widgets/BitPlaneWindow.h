#ifndef WIDGET_BITPLANEWINDOW
#define WIDGET_BITPLANEWINDOW

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <Algorithm/BitPlane.h>
#include <Image.h>
#include <Widgets/ImageWidgets/StandardImageWindow.h>
#include "BitPlaneChoice.h"

using namespace genericinterface;

namespace bitplane
{
  class BitPlaneWindow : public StandardImageWindow
  {
  Q_OBJECT

  public:
    BitPlaneWindow(const QString & path, GenericInterface* gi, Image* image);

  private slots:
    void changeMask();
  
  private:
    BitPlaneChoice* _bitplanechoice;
    Image* _workImg;
  };
}

#endif
