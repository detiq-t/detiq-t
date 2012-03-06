#include "GraphicsView.h"

using namespace genericinterface;
using namespace imagein;

GraphicsView::GraphicsView(Image* image): QGraphicsView(), _image(image)
{
	_scene = new QGraphicsScene();
	init();
}

void GraphicsView::init()
{
	showPixelsGrid();
}

void GraphicsView::showPixelsGrid()
{
    this->setMouseTracking(true); //Switch on mouse tracking (no need to press button)
    
    QImage im(_image->getWidth(), _image->getHeight(), QImage::Format_ARGB32);

    //on récupère les bits de l'image qt, qu'on cast en QRgb (qui fait 32 bits -> une image RGBA)
    QRgb* data = reinterpret_cast<QRgb*>(im.bits());
    Image::const_iterator it = _image->begin();
    std::cout << "Nombre de canaux : " << _image->getNbChannels() << std::endl;
    for(unsigned int i = 0 ; i < _image->getHeight()*_image->getWidth() ; ++i)
    {
        //Pour chaque pixel de l'image Qt, on récupère les données correspondantes de l'image ImageIn grace à l'itérateur
        if(_image->getNbChannels() == 4)
        {
			unsigned char red = *(it++);
			unsigned char green = *(it++);
			unsigned char blue = *(it++);
			unsigned char alpha = *(it++);

			//On utilise la fonction qRgba pour en faire un pointeur de qRgb
			data[i] = qRgba(red, green, blue, alpha);
		}
		else if(_image->getNbChannels() == 3)
		{
			unsigned char red = *(it++);
			unsigned char green = *(it++);
			unsigned char blue = *(it++);

			//On utilise la fonction qRgba pour en faire un pointeur de qRgb
			data[i] = qRgb(red, green, blue);		
		}
    }

    //Qt ne peut pas afficher les QImage directement, on en fait un QPixmap...
    _pixmap_img = new QPixmap();
    _pixmap_img->convertFromImage(im);
    
	_item = _scene->addPixmap(*_pixmap_img);
	
	for(unsigned int i = 0; i < _image->getWidth(); i++)
	{
		QGraphicsLineItem *line = new QGraphicsLineItem(i, 0, i, _image->getHeight());
		_scene->addItem(line);
	}
	for(unsigned int j = 0; j < _image->getHeight(); j++)
	{
		QGraphicsLineItem *line = new QGraphicsLineItem(0, j, _image->getWidth(), j);
		_scene->addItem(line);
	}
	this->setScene(_scene);
}

void GraphicsView::wheelEvent(QWheelEvent* event)
{
	if (/*_ctrlPressed && */event->orientation() == Qt::Vertical)
	{
		if(event->delta() < 0) //Zoom out
		{
			this->scale(0.95, 0.95);
		}
		else //Zoom in
		{
			this->scale(1.05, 1.05);
		}
		
		//emit zoomChanged(_zoomFactor*100);
	}
}

void GraphicsView::mousePressEvent(QMouseEvent * event)
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

void GraphicsView::mouseMoveEvent(QMouseEvent * event)
{
    if(event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
    {
		//TODO
		//	Récupérer la valeur
		emit pixelHovered(event->x(), event->y());
	}
}
