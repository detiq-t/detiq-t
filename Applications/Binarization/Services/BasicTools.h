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

#ifndef BASICTOOLS_H
#define BASICTOOLS_H

#include <Services/AlgorithmService.h>

#include <QMenu>

using namespace genericinterface;

/*!
* \brief A service that offers some basics tools
*/
class BasicTools : public AlgorithmService
{
    Q_OBJECT
public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

public slots:
    void applyIdentity();
    void applyInversion();
    void convertToGrayscale(); // call an algorithm to transform to a grayscale image

private:
    QMenu* _menu;
    QAction* _identity;
    QAction* _inversion;
    QAction* _convertToGrayscale;
};

#endif
