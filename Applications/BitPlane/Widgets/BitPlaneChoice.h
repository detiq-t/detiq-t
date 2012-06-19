/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

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
