#include "ResultWidget.h"

using namespace genericinterface;

ResultWidget::ResultWidget(unsigned int compNumber, double compSize, QWidget* parent)
 : QDialog(parent)
{
    _componentNumber = new QLabel(QString::number(compNumber));
    _averageComponentSize = new QLabel(QString::number(compSize));

    QFormLayout* layout = new QFormLayout;
    layout->addRow("Number of connected component : ", _componentNumber);
    layout->addRow("Average size of the components : ", _averageComponentSize);

    this->setLayout(layout);
}
