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
  _otsu = _toolBar->addAction("&Otsu");
  _manual = _toolBar->addAction("&Manual binarization");
}

void BinarizationService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);

  QObject::connect(_otsu, SIGNAL(triggered()), this, SLOT(applyOtsu()));
  QObject::connect(_manual, SIGNAL(triggered()), this, SLOT(applyManualBinarization()));
}


void BinarizationService::applyOtsu()
{
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        QString& path = siw->getPath();
        const Image* im = siw->getImage();
        Image* im_selected = im->crop(*(siw->getSelection()));

        Otsu algo;

        if (im_selected->getNbChannels() != 1)
        {
            QMessageBox::information(siw,
                                     "Attention",
                                     "You want to binarize a non grayscale image, it's impossible. You should first transform it.");
        }
        else
        {
            GrayscaleImage* im_tmp = Converter<GrayscaleImage>::convert(*im_selected);
            Image* im_res = algo(im_tmp);
            StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
            emit newImageWindowCreated(path, siw_res);


            int threshold = algo.getThreshold();
            OtsuWidget* otsuWidget = new OtsuWidget(siw, threshold);
            QMdiArea* area = (QMdiArea*)_gi->centralWidget();
            area->addSubWindow(otsuWidget);
            otsuWidget->show();
        }
    }
}


void BinarizationService::applyManualBinarization()
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
            _manualWidget = new ManualWidget(siw);
            QMdiArea* area = (QMdiArea*)_gi->centralWidget();
            area->addSubWindow(_manualWidget);
            _manualWidget->show();
        }
    }
}
