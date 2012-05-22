#include "MorphoMatService.h"
#include "../Widgets/StructElemWindow.h"

#include <GenericInterface.h>

#include <Algorithm/MorphoMat.h>
#include <Converter.h>

#include <QMessageBox>

using namespace genericinterface;
using namespace imagein::algorithm;

using namespace imagein::MorphoMat;

MorphoMatService::MorphoMatService() {

    bool elem[] = {
        false, true, false,
        true,  true, true,
        false, true, false
    };

    _structElem = new StructElem<depth_default_t>(GrayscaleImage_t<bool>(3, 3, elem), 1, 1);
}

void MorphoMatService::display(GenericInterface* gi)
{
  AlgorithmService::display(gi);

  _toolBar = gi->addToolBar("MorphoMat");
  _editStructElem = _toolBar->addAction("Element &structurant");
  _erosion = _toolBar->addAction("&Erosion");
  _dilatation = _toolBar->addAction("&Dilatation");
  _gradient = _toolBar->addAction("&Gradient");
}

void MorphoMatService::connect(GenericInterface* gi)
{
  AlgorithmService::connect(gi);

  QObject::connect(_editStructElem, SIGNAL(triggered()), this, SLOT(editStructElem()));
  QObject::connect(_erosion, SIGNAL(triggered()), this, SLOT(applyErosion()));
  QObject::connect(_dilatation, SIGNAL(triggered()), this, SLOT(applyDilatation()));
  QObject::connect(_gradient, SIGNAL(triggered()), this, SLOT(applyGradient()));
}


void MorphoMatService::editStructElem()
{
    StructElemWindow* structElemWindow = new StructElemWindow(_structElem);
    QMdiArea* area = (QMdiArea*)_gi->centralWidget();
    area->addSubWindow(structElemWindow);
    structElemWindow->show();
}

void MorphoMatService::applyErosion()
{
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* img = siw->getImage();
        QString& path = siw->getPath();
        //GrayscaleImage* im_tmp = Converter<GrayscaleImage>::convert(*im);
        MorphoMat::Erosion<depth8_t> algo(*_structElem);
        Image *res = algo(img);
        StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, res);
        emit newImageWindowCreated(path, siw_res);
    } 
}

void MorphoMatService::applyDilatation() {
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* img = siw->getImage();
        QString& path = siw->getPath();
        //GrayscaleImage* im_tmp = Converter<GrayscaleImage>::convert(*im);
        MorphoMat::Dilatation<depth8_t> algo(*_structElem);
        Image *res = algo(img);
        StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, res);
        emit newImageWindowCreated(path, siw_res);
    } 
}

void MorphoMatService::applyGradient() {
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* img = siw->getImage();
        QString& path = siw->getPath();
        //GrayscaleImage* im_tmp = Converter<GrayscaleImage>::convert(*im);
        MorphoMat::Gradient<depth8_t> algo(*_structElem);
        Image *res = algo(img);
        StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, res);
        emit newImageWindowCreated(path, siw_res);
    } 
}

