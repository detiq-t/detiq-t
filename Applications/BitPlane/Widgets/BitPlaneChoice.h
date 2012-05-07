#ifndef WIDGET_BITPLANECHOICE
#define WIDGET_BITPLANECHOICE

#include <QWidget>
#include <QLabel>
#include <QString>
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
    BitPlaneChoice(QWidget* parent);
    uint8_t getMask();
    QString getStrMask();

  signals:
    void newMaskAllocated();

  private slots:
    void maskChanged();
  
  private:
    QString* _StrMask;
    QLabel* _DisplayMask;
    QCheckBox* _CBbit0;
    QCheckBox* _CBbit1;
    QCheckBox* _CBbit2;
    QCheckBox* _CBbit3;
    QCheckBox* _CBbit4;
    QCheckBox* _CBbit5;
    QCheckBox* _CBbit6;
    QCheckBox* _CBbit7;
    uint8_t _currentMask;
  };
}

#endif
