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

#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <Services/AlgorithmService.h>
#include <Algorithm/ComponentLabeling.h>

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>

class OptionsWidget : public QDialog 
{
    Q_OBJECT
    public:
        OptionsWidget(QWidget* parent);
    
    signals:
        void optionsChosen(imagein::algorithm::ComponentLabeling*);

    private slots:
        void createAlgorithm();

    private:
        QWidget* _connectivityGroup; 
        QRadioButton* _connectivity_4;
        QRadioButton* _connectivity_8;

        QWidget* _backgroundColorGroup;
        QRadioButton* _backgroundColor_white;
        QRadioButton* _backgroundColor_black;

        QPushButton* ok;
};


#endif
