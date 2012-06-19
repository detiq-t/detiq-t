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

#ifndef BINARIZATIONSERVICE_H
#define BINARIZATIONSERVICE_H

#include <Services/AlgorithmService.h>
#include "BinarizationWidget.h"

#include <QToolBar>

using namespace genericinterface;

/*!
 * \brief Service that offers the possibility to Binarize an Image.
 *
 * It allow to use the Otsu's algorithm or to choose one or two manual thresholds.
 */
class BinarizationService : public AlgorithmService
{
    Q_OBJECT
public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

private slots:
    /**
     * \brief Open the widget to binarize the current Image.
     *
     * It will first check if the Image is a grayscale, if not it will display a message.
     */
    void applyBinarization();

    /**
     * \brief Extract the binarized image of the widget.
     *
     * \param path The path of the source image.
     * \param im The image from the widget.
     */
    void exportBinarizedImage(QString& path, Image* im);

    void aboutOtsu();

private:
    QAction* _binarize;
    BinarizationWidget* _binWidget;
};

#endif
