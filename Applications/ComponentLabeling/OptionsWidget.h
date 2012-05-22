#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <Services/AlgorithmService.h>
#include <Algorithm/ComponentLabeling.h>

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>

class OptionsWidget : public QDialog 
{
    Q_OBJECT
    public:
        OptionsWidget(QWidget* parent);
    
    signals:
        void optionsChosen(imagein::algorithm::ComponentLabeling*);

    private slots:
        void createAlgorithm();

    private:
        QWidget* _connectivityGroup; 
        QRadioButton* _connectivity_4;
        QRadioButton* _connectivity_8;

        QWidget* _backgroundColorGroup;
        QRadioButton* _backgroundColor_white;
        QRadioButton* _backgroundColor_black;

        QPushButton* ok;
};


#endif
