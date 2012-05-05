#include "BitPlaneChoice.h"

using namespace bitplane;
using namespace imagein;
using namespace algorithm;

BitPlaneChoice::BitPlaneChoice() : QWidget()
{
  setFixedSize(180, 120);
  _Introduction = new QLabel("Bit plane mask :", this);
  _Introduction->move(40,10);
  _CBbit0 = new QCheckBox(this);
  _CBbit0->setCheckState(Qt::Checked);
  _CBbit0->move(150,30);
  QObject::connect(_CBbit0, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  _CBbit1 = new QCheckBox(this);
  _CBbit1->setCheckState(Qt::Checked);
  _CBbit1->move(130,30);
  QObject::connect(_CBbit1, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  _CBbit2 = new QCheckBox(this);
  _CBbit2->setCheckState(Qt::Checked);
  _CBbit2->move(110,30);
  QObject::connect(_CBbit2, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  _CBbit3 = new QCheckBox(this);
  _CBbit3->setCheckState(Qt::Checked);
  _CBbit3->move(90,30);
  QObject::connect(_CBbit3, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  _CBbit4 = new QCheckBox(this);
  _CBbit4->setCheckState(Qt::Checked);
  _CBbit4->move(70,30);
  QObject::connect(_CBbit4, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  _CBbit5 = new QCheckBox(this);
  _CBbit5->setCheckState(Qt::Checked);
  _CBbit5->move(50,30);
  QObject::connect(_CBbit5, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  _CBbit6 = new QCheckBox(this);
  _CBbit6->setCheckState(Qt::Checked);
  _CBbit6->move(30,30);
  QObject::connect(_CBbit6, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  _CBbit7 = new QCheckBox(this);
  _CBbit7->setCheckState(Qt::Checked);
  _CBbit7->move(10,30);
  QObject::connect(_CBbit7, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  _StrMask = new QLabel("1 1 1 1 1 1 1 1", this);
  _StrMask->move(40,60);
  _PBvalidate = new QPushButton("Validate",this);
  _PBvalidate->move(50,90);
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

void BitPlaneChoice::maskChanged()
{
  std::string newMask = "";
  if(_CBbit7->isChecked()) newMask+="1 ";
  else newMask+="0 ";
  if(_CBbit6->isChecked()) newMask+="1 ";
  else newMask+="0 ";
  if(_CBbit5->isChecked()) newMask+="1 ";
  else newMask+="0 ";
  if(_CBbit4->isChecked()) newMask+="1 ";
  else newMask+="0 ";
  if(_CBbit3->isChecked()) newMask+="1 ";
  else newMask+="0 ";
  if(_CBbit2->isChecked()) newMask+="1 ";
  else newMask+="0 ";
  if(_CBbit1->isChecked()) newMask+="1 ";
  else newMask+="0 ";
  if(_CBbit0->isChecked()) newMask+="1";
  else newMask+="0";
  _StrMask->setText(newMask.c_str());
}
