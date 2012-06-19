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

#ifndef BINARIZATIONWIDGET_H
#define BINARIZATIONWIDGET_H

#include <GrayscaleImage.h>

#include <Widgets/ImageWidgets/StandardImageWindow.h>
#include <Widgets/ImageWidgets/HistogramWindow.h>

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QString>

using namespace genericinterface;

class BinarizationWidget : public QWidget
{
    Q_OBJECT
public:
    BinarizationWidget(StandardImageWindow* siw, const QString& id);

signals:
    void exportBinarizedImage(QString& path, Image* im);

private slots:
    void displayThresholdSelection(int index);
    void applyBinarization(int i);
    void exportBinarizedImage();

private:
    QString _originalPath;
    Image* _originalImage;
    GrayscaleImage* _originalGrayscaleImage;
    QComboBox* _nbThreshold;
    QLabel* _thresholdValue;
    QSpinBox* _firstThreshold;
    QSpinBox* _secondThreshold;

    HistogramWindow* _histo;
    StandardImageView* _binarizedImage;
};

#endif // MANUALWIDGET_H
