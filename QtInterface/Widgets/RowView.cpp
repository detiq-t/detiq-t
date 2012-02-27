#include "RowView.h"

using namespace genericinterface;

RowView::RowView(bool v): _vertical(v){
	init();
}

/*RowView::RowView(QWidget* parent, Image* image, bool v): AlternativeImageView(parent, image), _vertical(v)
{
	//TODO
	* Récupérer le profil de la ligne ou colonne sélectionnée et l'afficher
	if(_vertical)
	{
	
	}
	else
	{
	
	}
	init();
}*/

void RowView::init()
{
    this->setMouseTracking(true); //Switch on mouse tracking (no need to press button)
}

void RowView::mousePressEvent(QMouseEvent * event)
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

void RowView::mouseMoveEvent(QMouseEvent * event)
{
    if(event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
    {
		//TODO
		//	Récupérer la valeur
		emit valueHovered(0);
	}
}
