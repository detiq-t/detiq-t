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

#ifndef COMPONENTLABELINGSERVICE_H
#define COMPONENTLABELINGSERVICE_H

#include <Services/AlgorithmService.h>
#include <Algorithm/ComponentLabeling.h>

#include "OptionsWidget.h"
#include "ResultWidget.h"

/*!
* \brief Implementation of AlgorithmService for Component Labeling
*/
class ComponentLabelingService : public genericinterface::AlgorithmService
{
    Q_OBJECT
    public:
        void display(genericinterface::GenericInterface* gi);
        void connect(genericinterface::GenericInterface* gi);

        void applyAlgorithm(imagein::algorithm::ComponentLabeling* algo = NULL);

    public slots:
        void applyLabeling(imagein::algorithm::ComponentLabeling* algo = NULL) { this->applyAlgorithm(algo); }
        void showOptionsDialog();
        void checkActionsValid(QMdiSubWindow* activeWindow);

    private:
        QAction* _labeling;
};

#endif //FILTERINGSERVICE_H
