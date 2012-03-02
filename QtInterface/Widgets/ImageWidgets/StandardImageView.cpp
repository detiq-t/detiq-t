#include "StandardImageView.h"

using namespace genericinterface;

StandardImageView::StandardImageView(QWidget* parent): QLabel(), _parent(parent)//, _image(NULL)
{
    _highlight = new Rectangle();
    _selection = new Rectangle();
    _visibleArea = new Rectangle();
    init();
}

StandardImageView::StandardImageView(QWidget* parent, QString file): QLabel(), _parent(parent)
{
	_pixmap_img = new QPixmap(file);
	this->setPixmap(*_pixmap_img);
	this->setFixedSize(_pixmap_img->size());
	
	init();
}

StandardImageView::StandardImageView(QWidget* parent, Image* image): _parent(parent), _image(image)
{
    _highlight = new Rectangle();
    _selection = new Rectangle();
    _visibleArea = new Rectangle(0,0,_image->getWidth(), _image->getHeight());
    
    init();
    
    showImage();
}

void StandardImageView::init()
{
	/*_plot  = new QwtPlot();
    _grid = new QwtPlotGrid();
    _grid->attach(_plot);*/
    
    _zoomFactor = 1;
    _ctrlPressed = false;
    this->setMouseTracking(true); //Switch on mouse tracking (no need to press button)
	initMenu();
}

void StandardImageView::initMenu()
{
	_menu = new ImageContextMenu();
	_menu->setParent(this);
	
	_menu->addAction("Histogram", _parent, SLOT(showHistogram()));
	_menu->addAction("Pixels Grid", _parent, SLOT(showPixelsGrid()));
	_menu->addAction("Column Profile", _parent, SLOT(showColumnProfile()));
	_menu->addAction("Line Profile", _parent, SLOT(showLineProfile()));

	_menu->hide();	
}

void StandardImageView::showImage()
{
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

    //this->setStyleSheet("background-color: black;"); //L'arrière plan pour vérifier que la transparence a bien été préservée
    this->setPixmap(*_pixmap_img);
}

void StandardImageView::wheelEvent(QWheelEvent* event)
{
	if (_ctrlPressed && event->orientation() == Qt::Vertical)
	{
		if(event->delta() < 0 && _zoomFactor > 0.05) //Zoom out
		{
			_zoomFactor -= 0.05;
		}
		else //Zoom in
		{
			_zoomFactor += 0.05;
		}
		QPixmap pixmap_img = _pixmap_img->scaled((int)_pixmap_img->width()*_zoomFactor, (int)_pixmap_img->height()*_zoomFactor);
		this->setPixmap(pixmap_img);
		this->setFixedSize(pixmap_img.size());
		emit zoomChanged(_zoomFactor*100);
	}
}

void StandardImageView::mousePressEvent(QMouseEvent * event)
{
    if(event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
    {
		if(event->button() == Qt::RightButton)
		{
			_menu->move(event->x(), event->y());
			_menu->show();
		}
		else
		{
			_menu->hide();
			emit pixelClicked(event->x()/_zoomFactor, event->y()/_zoomFactor);
		}
	}
}

void StandardImageView::mouseMoveEvent(QMouseEvent * event)
{
    if(event->x() > 0 && event->x() < width() && event->y() > 0 && event->y() < height())
    {
		emit pixelHovered(event->x()/_zoomFactor, event->y()/_zoomFactor);
	}
}

void StandardImageView::ctrlPressed()
{
	_ctrlPressed = !_ctrlPressed;
}
