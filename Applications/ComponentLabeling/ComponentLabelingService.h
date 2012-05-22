#ifndef COMPONENTLABELINGSERVICE_H
#define COMPONENTLABELINGSERVICE_H

#include <Services/AlgorithmService.h>
#include <Algorithm/ComponentLabeling.h>

#include "OptionsWidget.h"
#include "ResultWidget.h"

/*!
* \brief Implementation of AlgorithmService for Component Labeling
*/
class ComponentLabelingService : public genericinterface::AlgorithmService
{
    Q_OBJECT
    public:
        void display(genericinterface::GenericInterface* gi);
        void connect(genericinterface::GenericInterface* gi);

        void applyAlgorithm(imagein::algorithm::ComponentLabeling* algo = NULL);

    public slots:
        void applyLabeling(imagein::algorithm::ComponentLabeling* algo = NULL) { this->applyAlgorithm(algo); }
        void showOptionsDialog();
        void checkActionsValid(QMdiSubWindow* activeWindow);

    private:
        QAction* _labeling;
};

#endif //FILTERINGSERVICE_H
