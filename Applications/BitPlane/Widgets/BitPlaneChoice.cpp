#include "BitPlaneChoice.h"

using namespace bitplane;
using namespace imagein;
using namespace algorithm;

BitPlaneChoice::BitPlaneChoice() : QWidget()
{
  setFixedSize(180, 100);
  _StrMask = new QLabel("Bit plane mask :", this);
  _StrMask->move(40,10);
  _CBbit0 = new QCheckBox(this);
  _CBbit0->setCheckState(Qt::Checked);
  _CBbit0->move(150,30);
  _CBbit1 = new QCheckBox(this);
  _CBbit1->setCheckState(Qt::Checked);
  _CBbit1->move(130,30);
  _CBbit2 = new QCheckBox(this);
  _CBbit2->setCheckState(Qt::Checked);
  _CBbit2->move(110,30);
  _CBbit3 = new QCheckBox(this);
  _CBbit3->setCheckState(Qt::Checked);
  _CBbit3->move(90,30);
  _CBbit4 = new QCheckBox(this);
  _CBbit4->setCheckState(Qt::Checked);
  _CBbit4->move(70,30);
  _CBbit5 = new QCheckBox(this);
  _CBbit5->setCheckState(Qt::Checked);
  _CBbit5->move(50,30);
  _CBbit6 = new QCheckBox(this);
  _CBbit6->setCheckState(Qt::Checked);
  _CBbit6->move(30,30);
  _CBbit7 = new QCheckBox(this);
  _CBbit7->setCheckState(Qt::Checked);
  _CBbit7->move(10,30);
  _PBvalidate = new QPushButton("Validate",this);
  _PBvalidate->move(50,70);
  QObject::connect(_PBvalidate, SIGNAL(clicked()), this, SLOT(validate()));
}

void BitPlaneChoice::validate()
{
  uint8_t mask = 0;
  if(_CBbit0->isChecked()) mask+=1;
  if(_CBbit1->isChecked()) mask+=2;
  if(_CBbit2->isChecked()) mask+=4;
  if(_CBbit3->isChecked()) mask+=8;
  if(_CBbit4->isChecked()) mask+=16;
  if(_CBbit5->isChecked()) mask+=32;
  if(_CBbit6->isChecked()) mask+=64;
  if(_CBbit7->isChecked()) mask+=128;
  BitPlane<Image>* bp = new BitPlane<Image>(mask);
  emit choiceValidate(bp);
}
