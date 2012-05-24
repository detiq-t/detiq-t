#include "AlgorithmService.h"
#include "../GenericInterface.h"

#include <Converter.h>

using namespace genericinterface;
using namespace imagein;

AlgorithmService::AlgorithmService()
{

}

void AlgorithmService::display(GenericInterface* gi)
{
  _toolBar = gi->addToolBar("Algorithm");
}

void AlgorithmService::connect(GenericInterface* gi)
{
  _gi = gi;

  WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
  QObject::connect(this, SIGNAL(newImageWindowCreated(const QString&, ImageWindow*)), ws, SLOT(addWidget(const QString&, ImageWindow*)));
}

/*
void AlgorithmService::applyAlgorithm(Algorithm_t<Image>* algo)
{
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* im = siw->getImage();
        Image* im_selected = im->crop(*(siw->getSelection()));
        QString& path = siw->getPath();
        Image* im_res = (*algo)(im_selected);
        //im_res = Converter<Image>::makeDisplayable(*im_res);
        StandardImageWindow* siw_res = new StandardImageWindow(path, _gi, im_res);
        emit newImageWindowCreated(path, siw_res);
    }
}
*/

void AlgorithmService::applyAlgorithm(Algorithm_t<Image>* algo)
{
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* whole_image = siw->getImage();
        const Image* im = whole_image->crop(*(siw->getSelection()));
        QString& name = siw->getPath();

        Image* im_res = (*algo)(im);
        //im_res = Converter<Image>::makeDisplayable(*im_res);

        StandardImageWindow* siw_res = new StandardImageWindow(name, _gi, im_res);
        emit newImageWindowCreated(name, siw_res);
    }
}

void AlgorithmService::applyAlgorithm(Algorithm_t<GrayscaleImage>* algo)
{
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* whole_image = siw->getImage();
        const Image* im = whole_image->crop(*(siw->getSelection()));
        QString& name = siw->getPath();

        if (im->getNbChannels() != 1) std::cout << "PUDDI PUDDI" << std::endl;
        GrayscaleImage* im_g = Converter<GrayscaleImage>::convert(*im);
        Image* im_res = (*algo)(im_g);
        //im_res = Converter<Image>::makeDisplayable(*im_res);

        StandardImageWindow* siw_res = new StandardImageWindow(name, _gi, im_res);
        emit newImageWindowCreated(name, siw_res);
    }
}
