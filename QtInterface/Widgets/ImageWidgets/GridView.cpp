#include "GridView.h"

using namespace genericinterface;

GridView::GridView(){
	init();
}

/*GridView::GridView(QWidget* parent, Image* image): AlternativeImageView(parent, image){
	//TODO
	* Récupérer la grille de l'image et l'afficher !
	init()
}*/

void GridView::init()
{
    this->setMouseTracking(true); //Switch on mouse tracking (no need to press button)
}

void GridView::mousePressEvent(QMouseEvent * event)
{
    if(event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
    {
		//TODO
		//	Récupérer les valeurs
		if(event->button() == Qt::RightButton)
		{
			emit pixelClickedRight(event->x(), event->y());
		}
		else
		{
			emit pixelClickedLeft(event->x(), event->y());
		}
	}
}

void GridView::mouseMoveEvent(QMouseEvent * event)
{
    if(event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
    {
		//TODO
		//	Récupérer la valeur
		emit pixelHovered(event->x(), event->y());
	}
}
