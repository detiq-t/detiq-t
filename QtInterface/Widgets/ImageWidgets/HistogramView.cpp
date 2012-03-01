#include "HistogramView.h"

using namespace genericinterface;

HistogramView::HistogramView()
{
	init();
}

/*HistogramView::HistogramView(QWidget* parent, Image* image): AlternativeImageView(parent, image)
{
	//TODO
	* Récupérer l'histogramme de l'image et l'afficher !
	Histogram histo = image->getHistogram(Integer channel, Rectangle frame);
	* init();
}*/

void HistogramView::init()
{
    this->setMouseTracking(true); //Switch on mouse tracking (no need to press button)
}

void HistogramView::mousePressEvent(QMouseEvent * event)
{
    if(event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
    {
		//TODO
		//	Récupérer les valeurs
		if(event->button() == Qt::RightButton)
		{
			emit valueClickedRight(2);
		}
		else
		{
			emit valueClickedLeft(1);
		}
	}
}

void HistogramView::mouseMoveEvent(QMouseEvent * event)
{
    if(event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
    {
		//TODO
		//	Récupérer la valeur
		emit valueHovered(0);
	}
}
