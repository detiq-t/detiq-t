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
  _toolBar = gi->toolBar("Algorithm");
}

void AlgorithmService::connect(GenericInterface* gi)
{
  _gi = gi;
  _ws = _gi->windowService();

  QObject::connect(this, SIGNAL(newImageWindowCreated(const QString&, ImageWindow*)), _ws, SLOT(addImage(const QString&, ImageWindow*)));
}

void AlgorithmService::applyAlgorithm(GenericAlgorithm_t<Image::depth_t>* algo)
{
    StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    if (siw != NULL)
    {
        const Image* whole_image = siw->getImage();
        const Image* im = whole_image->crop(*(siw->getSelection()));
        QString name = _ws->getWidgetId(siw);

        Image* im_res = (*algo)(im);
        //im_res = Converter<Image>::makeDisplayable(*im_res);

        StandardImageWindow* siw_res = new StandardImageWindow(name, _gi, im_res);
        emit newImageWindowCreated(name, siw_res);
    }
}
