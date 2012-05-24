#ifndef BINARIZATIONSERVICE_H
#define BINARIZATIONSERVICE_H

#include <Services/AlgorithmService.h>
#include "BinarizationWidget.h"

#include <QToolBar>

using namespace genericinterface;

/*!
 * \brief
 *
 *
 */
class BinarizationService : public AlgorithmService
{
    Q_OBJECT
public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

private slots:
    void applyBinarization();
    void exportBinarizedImage(QString& path, Image* im);

private:
    QToolBar* _toolBar;
    QAction* _binarize;
    BinarizationWidget* _binWidget;
};

#endif
