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

#ifndef QTINTERFACE_ALGORITHMSERVICE_H
#define QTINTERFACE_ALGORITHMSERVICE_H

#include "../Service.h"
#include "../Widgets/ImageWidgets/StandardImageWindow.h"

#include <Algorithm.h>
#include <GrayscaleImage.h>

#include <QToolBar>

namespace genericinterface
{
    class AlgorithmService : public QObject, public Service
    {
    Q_OBJECT
    public:
        AlgorithmService();

        virtual void display(GenericInterface* gi);
        virtual void connect(GenericInterface* gi);

        virtual void applyAlgorithm(imagein::GenericAlgorithm_t<Image::depth_t>* algo);

    signals:
        void newImageWindowCreated(const QString& path, ImageWindow* widget);

    protected:
        GenericInterface* _gi;
        WindowService* _ws;
        QToolBar* _toolBar;
    };
}

#endif
