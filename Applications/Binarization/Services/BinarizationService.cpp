#include "BinarizationService.h"
#include "../Widgets/OtsuWidget.h"

#include <GenericInterface.h>

#include <Algorithm/Binarization.h>
#include <Algorithm/Otsu.h>
#include <Converter.h>

#include <QMessageBox>

using namespace genericinterface;
using namespace imagein::algorithm;

void BinarizationService::display(GenericInterface* gi)
{
  AlgorithmService::display(gi);

  _toolBar = gi->addToolBar("Binarization");
  _binarize = _toolBar->addAction("&Binarization");
}

void BinarizationService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);

  QObject::connect(_binarize, SIGNAL(triggered()), this, SLOT(applyBinarization()));
}


void BinarizationService::applyBinarization()
{
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* im = siw->getImage();
        Image* im_selected = im->crop(*(siw->getSelection()));

        if (im_selected->getNbChannels() != 1)
        {
            QMessageBox::information(siw,
                                     "Attention",
                                     "You want to binarize a non grayscale image, it's impossible. You should first transform it.");
        }
        else
        {
            _binWidget = new BinarizationWidget(siw);
            QObject::connect(_binWidget, SIGNAL(exportBinarizedImage(QString&,Image*)),
                             this, SLOT(exportBinarizedImage(QString&,Image*)));
            QMdiArea* area = (QMdiArea*)_gi->centralWidget();
            area->addSubWindow(_binWidget);
            _binWidget->show();
        }
    }
}

void BinarizationService::exportBinarizedImage(QString& path, Image* im)
{
    StandardImageWindow* new_siw = new StandardImageWindow(path, _gi, im);
    emit newImageWindowCreated(path, new_siw);
}
