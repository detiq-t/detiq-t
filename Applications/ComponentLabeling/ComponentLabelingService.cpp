#include "ComponentLabelingService.h"

#include <GenericInterface.h>
#include <Converter.h>

using namespace genericinterface;
using namespace imagein::algorithm;
using namespace imagein;

void ComponentLabelingService::display(GenericInterface* gi)
{
    AlgorithmService::display(gi);

    _labeling = _toolBar->addAction("&Connected Component Labeling");
    _labeling->setEnabled(false);
}

void ComponentLabelingService::connect(GenericInterface* gi)
{
    AlgorithmService::connect(gi);

    QObject::connect(_labeling, SIGNAL(triggered()), this, SLOT(showOptionsDialog()));
	
    //connexion des changements d'images
    QObject::connect(_ws, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(checkActionsValid(QMdiSubWindow*)));
}

void ComponentLabelingService::showOptionsDialog()
{
    OptionsWidget* o = new OptionsWidget(_gi);

    QObject::connect(o, SIGNAL(optionsChosen(imagein::algorithm::ComponentLabeling*)), this, SLOT(applyLabeling(imagein::algorithm::ComponentLabeling*)));
    
    o->show();
}

void ComponentLabelingService::applyAlgorithm(ComponentLabeling* algo)
{
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* im = Converter<GrayscaleImage>::convert(*(siw->getImage()));
        QString id = _ws->getWidgetId(siw);
        RgbImage* im_res = (*algo)(im);
        StandardImageWindow* siw_res = new StandardImageWindow("", _gi, im_res);
        siw_res->setWindowTitle(ImageWindow::getTitleFromPath(id));
        _ws->addImage(id, siw_res);

        ResultWidget* r = new ResultWidget(algo->getNbComponents(), algo->getAverageComponentSize(), _gi);
        r->setWindowTitle(siw_res->windowTitle()+" - Statistiques");
        _ws->addWidget(id, r);
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
