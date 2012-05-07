#include "BitPlaneChoice.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

using namespace bitplane;
using namespace imagein;
using namespace algorithm;

BitPlaneChoice::BitPlaneChoice(QWidget* parent) : QWidget(parent)
{
  _StrMask = new QString("[1 1 1 1 1 1 1 1]");
  QVBoxLayout* mainLayout = new QVBoxLayout();
  mainLayout->setContentsMargins(0, 0, 0, 0);
  _DisplayMask = new QLabel("Bit plane mask [1 1 1 1 1 1 1 1] :", this);
  mainLayout->addWidget(_DisplayMask);

  QHBoxLayout* CBLayout = new QHBoxLayout();
  CBLayout->setContentsMargins(0, 0, 0, 0);
  _CBbit0 = new QCheckBox(this);
  _CBbit1 = new QCheckBox(this);
  _CBbit2 = new QCheckBox(this);
  _CBbit3 = new QCheckBox(this);
  _CBbit4 = new QCheckBox(this);
  _CBbit5 = new QCheckBox(this);
  _CBbit6 = new QCheckBox(this);
  _CBbit7 = new QCheckBox(this);
  _CBbit0->setCheckState(Qt::Checked);
  _CBbit1->setCheckState(Qt::Checked);
  _CBbit2->setCheckState(Qt::Checked);
  _CBbit3->setCheckState(Qt::Checked);
  _CBbit4->setCheckState(Qt::Checked);
  _CBbit5->setCheckState(Qt::Checked);
  _CBbit6->setCheckState(Qt::Checked);
  _CBbit7->setCheckState(Qt::Checked);
  QObject::connect(_CBbit0, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  QObject::connect(_CBbit1, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  QObject::connect(_CBbit2, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  QObject::connect(_CBbit3, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  QObject::connect(_CBbit4, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  QObject::connect(_CBbit5, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  QObject::connect(_CBbit6, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  QObject::connect(_CBbit7, SIGNAL(stateChanged(int)), this, SLOT(maskChanged()));
  CBLayout->addWidget(_CBbit7);
  CBLayout->addWidget(_CBbit6);
  CBLayout->addWidget(_CBbit5);
  CBLayout->addWidget(_CBbit4);
  CBLayout->addWidget(_CBbit3);
  CBLayout->addWidget(_CBbit2);
  CBLayout->addWidget(_CBbit1);
  CBLayout->addWidget(_CBbit0);
  QWidget* CBWidget = new QWidget();
  CBWidget->setLayout(CBLayout);

  mainLayout->addWidget(CBWidget);
  this->setLayout(mainLayout);

  _currentMask=255;
}

uint8_t BitPlaneChoice::getMask() {
  return _currentMask;
}

QString BitPlaneChoice::getStrMask() {
  return QString(_StrMask->toStdString().c_str());
}

void BitPlaneChoice::maskChanged()
{
  _currentMask=0;
  std::string newMask = "[";
  if(_CBbit7->isChecked()) {
    newMask+="1 ";
    _currentMask+=128;
  }
  else newMask+="0 ";
  if(_CBbit6->isChecked()) {
    newMask+="1 ";
    _currentMask+=64;
  }
  else newMask+="0 ";
  if(_CBbit5->isChecked()) {
    newMask+="1 ";
    _currentMask+=32;
  }
  else newMask+="0 ";
  if(_CBbit4->isChecked()) {
    newMask+="1 ";
    _currentMask+=16;
  }
  else newMask+="0 ";
  if(_CBbit3->isChecked()) {
    newMask+="1 ";
    _currentMask+=8;
  }
  else newMask+="0 ";
  if(_CBbit2->isChecked()) {
    newMask+="1 ";
    _currentMask+=4;
  }
  else newMask+="0 ";
  if(_CBbit1->isChecked()) {
    newMask+="1 ";
    _currentMask+=2;
  }
  else newMask+="0 ";
  if(_CBbit0->isChecked()) {
    newMask+="1]";
    _currentMask+=1;
  }
  else newMask+="0]";
  _StrMask = new QString(newMask.c_str());
  std::string newDisplayMask = "Bit plane mask " ;
  newDisplayMask+=newMask;
  newDisplayMask+=" :";
  _DisplayMask->setText(newDisplayMask.c_str());
  emit newMaskAllocated();
}
