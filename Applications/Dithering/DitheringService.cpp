#include "DitheringService.h"
#include <GenericInterface.h>
#include <GrayscaleImage.h>

#include <Converter.h>
#include <Algorithm/Dithering.h>

using namespace genericinterface;
using namespace imagein;
using namespace imagein::algorithm;


void DitheringService::display(GenericInterface* gi)
{
    AlgorithmService::display(gi);

    _dithering = _toolBar->addAction("&Dithering");
}

void DitheringService::connect(GenericInterface* gi)
{
    AlgorithmService::connect(gi);

    QObject::connect(_dithering, SIGNAL(triggered()), this, SLOT(applyDithering()));
}


void DitheringService::applyDithering()
{ 
    Dithering* algo = new Dithering;
    applyAlgorithm(algo);
    return;
    
	//StandardImageWindow* siw = dynamic_cast<StandardImageWindow*>(_ws->getCurrentImageWindow());
    //if (siw != NULL)
    //{
        //const Image* whole_image = siw->getImage();
        //const Image* im = whole_image->crop(*(siw->getSelection()));
        //QString name = _ws->getWidgetId(siw);

        //Image* im_res = (*algo)(Converter<GrayscaleImage>::convert(*im));
        ////im_res = Converter<Image>::makeDisplayable(*im_res);

        //StandardImageWindow* siw_res = new StandardImageWindow(name, _gi, im_res);
        //emit newImageWindowCreated(name, siw_res);
    //}
}
