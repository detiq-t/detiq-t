#include "StandardImageView.h"

using namespace genericinterface;

StandardImageView::StandardImageView(QWidget* parent, Image* image): QGraphicsPixmapItem(), _parent(parent), _image(image)
{
    _selection = new Rectangle(0, 0, _image->getWidth(), _image->getHeight());
    _visibleArea = new Rectangle(0, 0, _image->getWidth(), _image->getHeight());
	_scene = new QGraphicsScene();
    _view = new QGraphicsView();

	this->setAcceptHoverEvents(true);
    
	_zoomFactor = 1;
    _ctrlPressed = false;
    
    _mouseButtonPressed = false;
    _pixelClicked = new QPoint(-1, -1);
    
	initMenu();
    
    showImage();
}

void StandardImageView::initMenu()
{
	_menu = new ImageContextMenu(_view);
	_view->setContextMenuPolicy(Qt::CustomContextMenu);
	
	_menu->addAction("Histogram", _parent, SLOT(showHistogram()));
	_menu->addAction("Pixels Grid", _parent, SLOT(showPixelsGrid()));
	_menu->addAction("Column Profile", _parent, SLOT(showColumnProfile()));
	_menu->addAction("Line Profile", _parent, SLOT(showLineProfile()));

	QObject::connect(_view, SIGNAL(customContextMenuRequested(const QPoint&)), _menu, SLOT(showContextMenu(const QPoint&)));
}

void StandardImageView::showImage()
{
    QImage im(_image->getWidth(), _image->getHeight(), QImage::Format_ARGB32);

    //on récupère les bits de l'image qt, qu'on cast en QRgb (qui fait 32 bits -> une image RGBA)
    QRgb* data = reinterpret_cast<QRgb*>(im.bits());
    Image::const_iterator it = _image->begin();
    
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
    
    this->setPixmap(*_pixmap_img);
	_scene->addItem(this);
	
	_highlight = new QGraphicsRectItem(((int)_selection->x) - 1, ((int)_selection->y) - 1, ((int)_selection->w) + 1, ((int)_selection->h) + 1);
	_highlight->setPen(QPen(QBrush(QColor(255, 0, 0, 100)), 1.5));
	
	_scene->addItem(_highlight);
	
	_view->setScene(_scene);
}

void StandardImageView::wheelEvent(QGraphicsSceneWheelEvent* event)
{
	if (_ctrlPressed && event->orientation() == Qt::Vertical)
	{
		double wOrigin = _pixmap_img->width();
		double hOrigin = _pixmap_img->height();
		if(event->delta() < 0 && _zoomFactor > 0.05) //Zoom out
		{
			_zoomFactor -= 0.05;
			
			double wActual = wOrigin * (_zoomFactor + 0.05);
			double hActual = hOrigin * (_zoomFactor + 0.05);
			
			double zoomW = (_zoomFactor * wOrigin) / wActual;
			double zoomH = (_zoomFactor * hOrigin) / hActual;
			
			_view->scale(zoomW, zoomH);
		}
		else if(event->delta() > 0)//Zoom in
		{
			_zoomFactor += 0.05;
			
			double wActual = wOrigin * (_zoomFactor - 0.05);
			double hActual = hOrigin * (_zoomFactor - 0.05);
			
			double zoomW = (_zoomFactor * wOrigin) / wActual;
			double zoomH = (_zoomFactor * hOrigin) / hActual;
			
			_view->scale(zoomW, zoomH);
		}		
		
		emit zoomChanged(_zoomFactor*100);
	}
}

void StandardImageView::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	int x = event->pos().x();
	int y = event->pos().y();
    if(x >= 0 && x < pixmap().width() && y >= 0 && y < pixmap().height())
    {
		if(event->button() == Qt::LeftButton)
		{
			_mouseButtonPressed = true;
			_pixelClicked->setX(x);
			_pixelClicked->setY(y);
		}
	}
}

void StandardImageView::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	int x = event->pos().x();
	int y = event->pos().y();
	if(x >= 0 && x < pixmap().width() && y >= 0 && y < pixmap().height())
    {
		if(event->button() == Qt::LeftButton)
		{
			if(x == _pixelClicked->x() && y == _pixelClicked->y())
				emit pixelClicked(x, y);
			
			_mouseButtonPressed = false;
			_pixelClicked->setX(-1);
			_pixelClicked->setY(-1);
		}
	}
}

void StandardImageView::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    int x = event->pos().x();
	int y = event->pos().y();
    
    if(x >= 0 && x < pixmap().width() && y >= 0 && y < pixmap().height())
    {
		if(_mouseButtonPressed)
		{
			if(_pixelClicked->x() < x)
			{
				_selection->w = x - _pixelClicked->x();
				_selection->x = _pixelClicked->x();
				if(_pixelClicked->y() < y)
				{
					_highlight->setRect(_pixelClicked->x(), _pixelClicked->y(), x - _pixelClicked->x(), y - _pixelClicked->y());
					_selection->y = _pixelClicked->y();
					_selection->h = y - _pixelClicked->y();
				}
				else
				{
					_highlight->setRect(_pixelClicked->x(), y, x - _pixelClicked->x(), _pixelClicked->y() - y);
					_selection->y = y;
					_selection->h = _pixelClicked->y() - y;
				}
			}
			else
			{
				_selection->x = x;
				_selection->w = _pixelClicked->x() - x;
				if(_pixelClicked->y() < y)
				{
					_highlight->setRect(x, _pixelClicked->y(), _pixelClicked->x() - x, y - _pixelClicked->y());
					_selection->y = _pixelClicked->y();
					_selection->h = y - _pixelClicked->y();
				}
				else
				{
					_highlight->setRect(x, y, _pixelClicked->x() - x, _pixelClicked->y() - y);
					_selection->y = y;
					_selection->h = _pixelClicked->y() - y;
				}
			}
		}
	}
}

void StandardImageView::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
	emit pixelHovered((int)event->pos().x(), (int)event->pos().y());
}


void StandardImageView::ctrlPressed()
{
	_ctrlPressed = !_ctrlPressed;
}

void StandardImageView::showHighlightRect(imagein::Rectangle* rect)
{
	_highlight->setRect(((int)rect->x), ((int)rect->y), ((int)rect->w), ((int)rect->h));
}
