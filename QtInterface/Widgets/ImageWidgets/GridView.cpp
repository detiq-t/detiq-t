#include "GridView.h"

using namespace genericinterface;

GridView::GridView(Image* image): AlternativeImageView(image){
	_view = new GraphicsView(image);
	
	_view->setBackgroundRole(QPalette::Dark);
	_view->setAlignment(Qt::AlignCenter);
}

GraphicsView* GridView::getGraphicsView()
{
	return _view;
}

/*void StandardImageView::ctrlPressed()
{
	_ctrlPressed = !_ctrlPressed;
}*/
