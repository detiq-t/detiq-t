#include "ComponentLabelingService.h"

#include <GenericInterface.h>
#include <Converter.h>
#include <QDebug>

using namespace genericinterface;
using namespace imagein::algorithm;
using namespace imagein;

void ComponentLabelingService::display(GenericInterface* gi)
{

    _gi = gi;
    QToolBar* toolBar = gi->addToolBar("Algorithms");
    _labeling = toolBar->addAction("&Connected Component Labeling");
    _labeling->setEnabled(false);
}

void ComponentLabelingService::connect(GenericInterface* gi)
{
    AlgorithmService::connect(gi);

    QObject::connect(_labeling, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));
	
    //connexion des changements d'images
	WindowService* ws = dynamic_cast<WindowService*>(gi->getService(GenericInterface::WINDOW_SERVICE));
	QObject::connect(ws, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(checkActionsValid(QMdiSubWindow*)));
}

void ComponentLabelingService::showOptionsDialog()
{
    OptionsWidget* o = new OptionsWidget(_gi);

    QObject::connect(o, SIGNAL(optionsChosen(imagein::algorithm::ComponentLabeling*)), this, SLOT(applyLabeling(imagein::algorithm::ComponentLabeling*)));
    
    o->show();
}

void ComponentLabelingService::applyAlgorithm(ComponentLabeling* algo)
{
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* im = Converter<GrayscaleImage>::convert(*(siw->getImage()));
        QString id = ws->getWidgetId(siw);
        RgbImage* im_res = (*algo)(im);
        StandardImageWindow* siw_res = new StandardImageWindow("", _gi, im_res);
        ws->addImage(id, siw_res);

        ResultWidget* r = new ResultWidget(algo->getNbComponents(), algo->getAverageComponentSize(), _gi);
        ws->addWidget(id, r);
    }
}

void ComponentLabelingService::checkActionsValid(QMdiSubWindow* activeWindow)
{
	StandardImageWindow* window = (activeWindow) ? dynamic_cast<StandardImageWindow*>(activeWindow->widget()) : NULL;
	if(window) {
		_labeling->setEnabled(true);
	}
	else {
		_labeling->setEnabled(false);
	}
}
