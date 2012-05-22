#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include <Services/AlgorithmService.h>

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>

class ResultWidget : public QDialog 
{
    public:
        ResultWidget(unsigned int compNumber, double compSize, QWidget* parent);

    private:
        QLabel* _componentNumber;
        QLabel* _averageComponentSize;
};


#endif
