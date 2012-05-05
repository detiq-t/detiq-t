#ifndef WIDGET_BITPLANECHOICE
#define WIDGET_BITPLANECHOICE

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <Algorithm/BitPlane.h>
#include <Image.h>

namespace bitplane
{
  class BitPlaneChoice : public QWidget
  {
  Q_OBJECT

  public:
    BitPlaneChoice();

  signals:
    void choiceValidate(imagein::algorithm::BitPlane<imagein::Image>* bitplanealgo);

  private slots:
    void validate();
    void maskChanged();
  
  private:
    QLabel* _Introduction;
    QLabel* _StrMask;
    QCheckBox* _CBbit0;
    QCheckBox* _CBbit1;
    QCheckBox* _CBbit2;
    QCheckBox* _CBbit3;
    QCheckBox* _CBbit4;
    QCheckBox* _CBbit5;
    QCheckBox* _CBbit6;
    QCheckBox* _CBbit7;
    QPushButton* _PBvalidate;
  };
}

#endif
