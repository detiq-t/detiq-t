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

#include "OptionsWidget.h"

using namespace imagein;
using namespace genericinterface;
using namespace imagein::algorithm;

OptionsWidget::OptionsWidget(QWidget* parent)
 : QDialog(parent)
{
    this->setModal(true);

    _connectivityGroup = new QWidget(this);
    _connectivity_4 = new QRadioButton("4", _connectivityGroup);
    _connectivity_8 = new QRadioButton("8", _connectivityGroup);
    QHBoxLayout* cLayout = new QHBoxLayout;
    cLayout->addWidget(_connectivity_4);
    cLayout->addWidget(_connectivity_8);
    _connectivityGroup->setLayout(cLayout);
    _connectivity_4->setChecked(true);

    _backgroundColorGroup = new QWidget(this);
    _backgroundColor_white = new QRadioButton("white", _backgroundColorGroup);
    _backgroundColor_black = new QRadioButton("black", _backgroundColorGroup);
    QHBoxLayout* bLayout = new QHBoxLayout;
    bLayout->addWidget(_backgroundColor_white);
    bLayout->addWidget(_backgroundColor_black);
    _backgroundColorGroup->setLayout(bLayout);
    _backgroundColor_white->setChecked(true);


    QFormLayout* layout = new QFormLayout;
    layout->addRow("Pixel connectivity", _connectivityGroup);
    layout->addRow("Background color", _backgroundColorGroup);

    ok = new QPushButton("Apply", this);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addWidget(ok);

    this->setLayout(mainLayout);
    this->setFixedSize(sizeHint());

    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(createAlgorithm()));
}

void OptionsWidget::createAlgorithm()
{
    ComponentLabeling::Connectivity c = (_connectivity_8->isChecked()) ? ComponentLabeling::CONNECT_8 : ComponentLabeling::CONNECT_4;
    bool blackBackground = _backgroundColor_black->isChecked();
    bool binarizeInput = true;
    ComponentLabeling algo(c, blackBackground, binarizeInput);

    emit optionsChosen(&algo);

    this->close();
}
