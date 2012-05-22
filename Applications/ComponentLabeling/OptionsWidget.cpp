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
