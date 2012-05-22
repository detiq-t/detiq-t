#include "StructElemWindow.h"
#include "StructElemViewer.h"

#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

#include <Image.h>

using namespace genericinterface;
using namespace imagein;
using namespace imagein::algorithm;
using namespace imagein::MorphoMat;

StructElemWindow::StructElemWindow(StructElem<depth_default_t>*& elem) : _structElem(elem), _serviceStructElem(elem)
{
    _realSize = elem->getElem();
    
    _widget = new QWidget;
    this->setWidget(_widget);

    QVBoxLayout* layout = new QVBoxLayout();
    _toolBar = new QToolBar;
    _openFile = _toolBar->addAction("&Ouvrir un fichier");
    _saveFile = _toolBar->addAction("&Sauvegarder sous...");
    layout->addWidget(_toolBar);
    _widget->setLayout(layout);

    QFormLayout* formLayout = new QFormLayout();
    layout->addLayout(formLayout);
    QSpinBox* spinBox = new QSpinBox();
    spinBox->setRange(1,32);
    spinBox->setSingleStep(1);
    spinBox->setSuffix("");
    spinBox->setValue(_structElem->getScale());
    formLayout->insertRow(1, "Echelle :", spinBox);
    QComboBox* comboBox = new QComboBox;
    comboBox->setEditable(false);
    comboBox->insertItem(0, "Diamant");
    comboBox->insertItem(1, "Disque");
    _viewer = new StructElemViewer(*_structElem);
    _view = new QGraphicsView;
    _view->setScene(_viewer);
    layout->addWidget(_view);
    _viewer->draw(0,0);
    //QObject::connect(_viewer, SIGNAL(positionUpdated(int, int)), viewer, SLOT(draw(int, int)));
    QPushButton* button = new QPushButton("Valider");
    layout->addWidget(button);
  
    QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(ok()));
    QObject::connect(_openFile, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(_saveFile, SIGNAL(triggered()), this, SLOT(saveFile()));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(resize(int)));
}

void StructElemWindow::ok() {
    _serviceStructElem = _structElem;
    this->close();
}

void StructElemWindow::diamond() {

}

void StructElemWindow::resize(int size) {
    /*unsigned int size = std::abs(size_);
    GrayscaleImage_t<bool> elem(_realSize.getWidth()*size, _realSize.getHeight()*size);
    for(unsigned int j = 0; j < elem.getHeight(); ++j) {
        for(unsigned int i = 0; i < elem.getWidth(); ++i) {
            elem.setPixel(i, j, _realSize.getPixel(i/size, j/size));
        }
    }*/

    //StructElem<depth_default_t>* structElem = new StructElem<depth_default_t>(elem, elem.getWidth()/2, elem.getHeight()/2);
    _structElem->setScale(std::abs(size));
    changeStructElem(_structElem);
}

void StructElemWindow::changeStructElem(imagein::MorphoMat::StructElem<depth_default_t>* elem) {
    _structElem = elem;
    StructElemViewer* newViewer = new StructElemViewer(*_structElem);
    _view->setScene(newViewer);
    delete _viewer;
    _viewer = newViewer;
    _viewer->draw(0,0);
}

void StructElemWindow::openFile() {
    QString file = QFileDialog::getOpenFileName(this, "Open a file", QString(), "Images (*.png *.bmp *.jpg *.jpeg)");
    Image image(file.toStdString());
    Otsu algo;
    GrayscaleImage* im_tmp = Converter<GrayscaleImage>::convert(image);
    GrayscaleImage* im_res = algo(im_tmp);
    GrayscaleImage_t<bool> elem(im_res->getWidth(), im_res->getHeight());
    for(unsigned int j = 0; j < elem.getHeight(); ++j) {
        for(unsigned int i = 0; i < elem.getWidth(); ++i) {
            elem.setPixel(i, j, (im_res->getPixel(i, j) <= 0));
        }
    }

    StructElem<depth_default_t>* structElem = new StructElem<depth_default_t>(elem, elem.getWidth()/2, elem.getHeight()/2);
    changeStructElem(structElem);
    _realSize = elem;
    
}

void StructElemWindow::saveFile() {
    QString file = QFileDialog::getSaveFileName(this, "Save file", QString(), "Images (*.png *.bmp *.jpg *.jpeg)");

    GrayscaleImage img(_structElem->getElem().getWidth(), _structElem->getElem().getHeight());
    for(unsigned int j = 0; j < img.getHeight(); ++j) {
        for(unsigned int i = 0; i < img.getWidth(); ++i) {
            img.setPixel(i, j, _structElem->getElem().getPixel(i, j) ? 0 : 255);
        }
    }
    img.save(file.toStdString());

    
}
