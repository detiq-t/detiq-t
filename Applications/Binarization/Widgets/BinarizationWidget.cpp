#include "BinarizationWidget.h"

#include <Image.h>
#include <Converter.h>
#include <Algorithm/Binarization.h>
#include <Algorithm/Otsu.h>

#include <QPushButton>

using namespace genericinterface;
using namespace imagein;
using namespace imagein::algorithm;

BinarizationWidget::BinarizationWidget(StandardImageWindow* siw) : _originalPath(siw->getPath())
{
    this->setWindowTitle("Binarization tool on " + siw->getName());

    // backing up the image we're working on while converting it into a grayscale image
    _originalImage = Converter<GrayscaleImage>::convert(*siw->getImage());

    // setting the layout
    QGridLayout* layout = new QGridLayout;
    this->setLayout(layout);

    // Top left panel = threshold
    QVBoxLayout* thresholdLayout = new QVBoxLayout;
    _nbThreshold = new QComboBox(this);
    _nbThreshold->addItem("Otsu method");
    _nbThreshold->addItem("Manual: one threshold");
    _nbThreshold->addItem("Manual: two thresholds");
    QObject::connect(_nbThreshold, SIGNAL(currentIndexChanged(int)), this, SLOT(displayThresholdSelection(int)));
    _thresholdValue = new QLabel(this);
    _firstThreshold = new QSpinBox(this);
    _firstThreshold->setMinimum(0);
    _firstThreshold->setMaximum(255);
    QObject::connect(_firstThreshold, SIGNAL(valueChanged(int)), this, SLOT(applyBinarization(int)));
    _secondThreshold = new QSpinBox(this);
    _secondThreshold->setMinimum(0);
    _secondThreshold->setMaximum(255);
    QObject::connect(_secondThreshold, SIGNAL(valueChanged(int)), this, SLOT(applyBinarization(int)));
    thresholdLayout->addWidget(_nbThreshold);
    thresholdLayout->addWidget(_thresholdValue);
    thresholdLayout->addWidget(_firstThreshold);
    thresholdLayout->addWidget(_secondThreshold);
    _firstThreshold->hide(); // initially we begin with Otsu method so we hide for manual binarization
    _secondThreshold->hide();
    layout->addLayout(thresholdLayout, 0, 0);

    // Top right panel
    QPushButton* button = new QPushButton("Export binarized image", this);
    QObject::connect(button, SIGNAL(clicked()), this, SLOT(exportBinarizedImage()));
    layout->addWidget(button, 0, 1);


    // Bottom left panel = histogram
    Rectangle* rect = new Rectangle(); //TODO Faire rectangle total sur une image
    _histo = new HistogramWindow(siw->getPath(), siw->getImage(), rect, NULL);
    layout->addWidget(_histo, 1, 0);


    // Bottom right panel = binarized image
    _binarizedImage = new StandardImageView(this, new Image(*(siw->getImage())));
    layout->addWidget(_binarizedImage->getGraphicsView(), 1, 1);

    // Once everything created, we call a binarization with Otsu's algorithm
     applyBinarization(0);
}

void BinarizationWidget::displayThresholdSelection(int index)
{
    if (index == 0)
    {
        _thresholdValue->show();
        _firstThreshold->hide();
        _secondThreshold->hide();
        applyBinarization(0);
    }
    if (index == 1)
    {
        _thresholdValue->hide();
        _firstThreshold->show();
        _secondThreshold->hide();
    }
    if (index == 2)
    {
        _thresholdValue->hide();
        _firstThreshold->show();
        _secondThreshold->show();
    }
}

void BinarizationWidget::applyBinarization(int i)
{
    if (_nbThreshold->currentIndex() == 0)
    {
        Otsu algo;
        Image* im_res = algo(_originalImage);
        _binarizedImage->setImage(im_res);
        _thresholdValue->setText("Threshold: " + QString::number(algo.getThreshold()));
    }
    if (_nbThreshold->currentIndex() == 1)
    {
        Binarization algo(_firstThreshold->value());
        Image* im_res = algo(_originalImage);
        _binarizedImage->setImage(im_res);
    }
    if (_nbThreshold->currentIndex() == 2)
    {
        Binarization algo(_firstThreshold->value(), _secondThreshold->value(), false);
        Image* im_res = algo(_originalImage);
        _binarizedImage->setImage(im_res);
    }

}

void BinarizationWidget::exportBinarizedImage()
{
    Image* im = new Image(*(_binarizedImage->getImage()));
    emit exportBinarizedImage(_originalPath, im);
}