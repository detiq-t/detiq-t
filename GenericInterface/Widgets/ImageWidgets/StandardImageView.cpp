#include "StandardImageView.h"

using namespace genericinterface;
using namespace imagein;

StandardImageView::StandardImageView(QWidget* parent, Image* image): QGraphicsPixmapItem(), _parent(parent), _image(image)
{
  _selection = new Rectangle(0, 0, _image->getWidth(), _image->getHeight());
  _visibleArea = new Rectangle(0, 0, _image->getWidth(), _image->getHeight());
	_scene = new QGraphicsScene();
  _view = new QGraphicsView();

	this->setAcceptHoverEvents(true);
    
	_zoomFactor = 1;
  _ctrlPressed = false;
  
  _sourceHighlight = NULL;
  _originalHighlight = new Rectangle(0, 0, _image->getWidth(), _image->getHeight());
  _resize = false;
  _originX = false;
  _originY = false;
  _vLine = false;
  _hLine = false;
  
  _mouseButtonPressed = false;
  _pixelClicked = new QPoint(-1, -1);
    
	initMenu();
    
  showImage();
}

StandardImageView::~StandardImageView()
{
	delete _selection;
	delete _visibleArea;
	delete _pixelClicked;
	delete _menu;
	delete _pixmap_img;
  delete _originalHighlight;
}

void StandardImageView::initMenu()
{
	_menu = new ImageContextMenu(_view);
	_view->setContextMenuPolicy(Qt::CustomContextMenu);
	
	_menu->addAction("Histogram", _parent, SLOT(showHistogram()));
	_menu->addAction("Horizontal Projection Histogram", _parent, SLOT(showHProjectionHistogram()));
	_menu->addAction("Vertical Projection Histogram", _parent, SLOT(showVProjectionHistogram()));
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
		else if(_image->getNbChannels() == 2)
		{
			unsigned char gray = *(it++);
			unsigned char alpha = *(it++);

			//On utilise la fonction qRgba pour en faire un pointeur de qRgb
			data[i] = qRgba(gray, gray, gray, alpha);		
		}
		else if(_image->getNbChannels() == 1)
		{
			unsigned char gray = *(it++);

			//On utilise la fonction qRgba pour en faire un pointeur de qRgb
			data[i] = qRgb(gray, gray, gray);			
		}
    }

    //Qt ne peut pas afficher les QImage directement, on en fait un QPixmap...
    _pixmap_img = new QPixmap();
    _pixmap_img->convertFromImage(im);
    
    this->setPixmap(*_pixmap_img);
	_scene->addItem(this);
	
	_highlight = new QGraphicsRectItem(((int)_selection->x), ((int)_selection->y), ((int)_selection->w), ((int)_selection->h));
	_highlight->setPen(QPen(QBrush(QColor(255, 0, 0, 200)), 1));
	
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
  
      int posX = QCursor::pos().x(), posY = QCursor::pos().y();
      if(x >= _highlight->rect().x() - 2 && x <= _highlight->rect().x() + 2)
        posX = QCursor::pos().x() + _highlight->rect().x() - x;
      if(x >= _highlight->rect().x() + _highlight->rect().width() - 2 && x <= _highlight->rect().x() + _highlight->rect().width() + 2)
        posX = QCursor::pos().x() + _highlight->rect().x() + _highlight->rect().width() - x;
      
      if(y >= _highlight->rect().y() - 2 && y <= _highlight->rect().y() + 2)
        posY = QCursor::pos().y() + _highlight->rect().y() - y;
      else if(y >= _highlight->rect().y() + _highlight->rect().height() - 2 && y <= _highlight->rect().y() + _highlight->rect().height() + 2)
        posY = QCursor::pos().y() + _highlight->rect().y() + _highlight->rect().height() - y;
      
      QCursor::setPos(posX, posY);
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
      
      _originalHighlight->x = _selection->x;
      _originalHighlight->y = _selection->y;
      _originalHighlight->h = _selection->h;
      _originalHighlight->w = _selection->w;
		}
	}
}

void StandardImageView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    qreal x = event->pos().x();
    qreal y = event->pos().y();

    if(x >= 0 && x < pixmap().width() && y >= 0 && y < pixmap().height())
    {
        if(_mouseButtonPressed)
        {
            if(_move)
            {
                int newX = _selection->x - (_pixelClicked->x() - x);
                int newY = _selection->y - (_pixelClicked->y() - y);
                if(!_hLine)
                    _selection->x = newX < 0 ? 0 : newX + _selection->w >= _image->getWidth() ? _image->getWidth() - _selection->w - 1 : newX;
                if(!_vLine)
                    _selection->y = newY < 0 ? 0 : newY + _selection->h >= _image->getHeight() ? _image->getHeight() - _selection->h - 1 : newY;
                _pixelClicked->setX(x);
                _pixelClicked->setY(y);
                if(_sourceHighlight != NULL)
                    _sourceHighlight->update(_selection);
            }
            else if(_resize && this->hasCursor())
            {
                if(this->cursor().shape() == Qt::SizeHorCursor || this->cursor().shape() == Qt::SizeFDiagCursor || this->cursor().shape() == Qt::SizeBDiagCursor)
                {
                    if(_originX && x < _originalHighlight->x  + _originalHighlight->w)
                    {
                        _selection->w = _originalHighlight->x - x + _originalHighlight->w;
                        _selection->x = x;
                    }
                    else if(_originX)
                    {
                        _originalHighlight->x = _originalHighlight->x + _originalHighlight->w;
                        _originalHighlight->w = x - _originalHighlight->x;
                        _originX = false;
                    }

                    if(!_originX && _originalHighlight->x >= x)
                    {
                        _selection->w = _originalHighlight->x - x;
                        _selection->x = x;
                    }
                    else if(!_originX)
                    {
                        _selection->w = x - _originalHighlight->x;
                        _selection->x = _originalHighlight->x;
                    }
                }

                if(this->cursor().shape() == Qt::SizeVerCursor || this->cursor().shape() == Qt::SizeFDiagCursor || this->cursor().shape() == Qt::SizeBDiagCursor)
                {
                    if(_originY && y < _originalHighlight->y  + _originalHighlight->h)
                    {
                        _selection->h = _originalHighlight->y - y + _originalHighlight->h;
                        _selection->y = y;
                    }
                    else if(_originY)
                    {
                        _originalHighlight->y = _originalHighlight->y + _originalHighlight->h;
                        _originalHighlight->h = y - _originalHighlight->y;
                        _originY = false;
                    }

                    if(!_originY && _originalHighlight->y >= y)
                    {
                        _selection->h = _originalHighlight->y - y;
                        _selection->y = y;
                    }
                    else if(!_originY)
                    {
                        _selection->h = y - _originalHighlight->y;
                        _selection->y = _originalHighlight->y;
                    }
                }
                if(_sourceHighlight != NULL)
                    _sourceHighlight->update(_selection);
            }
            else
            {
                _sourceHighlight = NULL;
                if(_pixelClicked->x() < x)
                {
                    _selection->w = x - _pixelClicked->x();
                    _selection->x = _pixelClicked->x();
                }
                else
                {
                    _selection->x = x;
                    _selection->w = _pixelClicked->x() - x;
                }

                if(_pixelClicked->y() < y)
                {
                    _selection->y = _pixelClicked->y();
                    _selection->h = y - _pixelClicked->y();
                }
                else
                {
                    _selection->y = y;
                    _selection->h = _pixelClicked->y() - y;
                }
            }
            _highlight->setRect(_selection->x, _selection->y, _selection->w, _selection->h);
        }
    }
}

void StandardImageView::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
  int x = event->pos().x();
	int y = event->pos().y();
  
	emit pixelHovered(x, y);
  
  if(!_mouseButtonPressed)
      this->setCursor(mouseOverHighlight(x, y));
}

Qt::CursorShape StandardImageView::mouseOverHighlight(int x, int y)
{
  Qt::CursorShape res = Qt::ArrowCursor;
  
  _originX = false;
  _originY = false;
  
  if(_vLine && x >= _highlight->rect().x() - 2 && x <= _highlight->rect().x() + 2)
      res = Qt::SizeAllCursor;
  else if(_hLine && y >= _highlight->rect().y() - 2 && y <= _highlight->rect().y() + 2)
      res = Qt::SizeAllCursor;
  
  if(x >= _highlight->rect().x() - 2 && x <= _highlight->rect().x() + 2)
  {
    if(_ctrlPressed)
      res = Qt::SizeAllCursor;
    else
    {
      _originX = true;
      if(y >= _highlight->rect().y() - 2 && y <= _highlight->rect().y() + 2)
      {
        _originY = true;
        res = Qt::SizeFDiagCursor;
      }
      else if(res == Qt::ArrowCursor && (y >= _highlight->rect().y() + _highlight->rect().height() - 2 && y <= _highlight->rect().y() + _highlight->rect().height() + 2))
        res = Qt::SizeBDiagCursor;
      else if(res == Qt::ArrowCursor && (y >= _highlight->rect().y() - 2 && y <= _highlight->rect().y() + _highlight->rect().height() + 2))
        res = Qt::SizeHorCursor;
    }
  }
    
  if(res == Qt::ArrowCursor && (x >= _highlight->rect().x() + _highlight->rect().width() - 2 && x <= _highlight->rect().x() + _highlight->rect().width() + 2))
  {
    if(_ctrlPressed)
      res = Qt::SizeAllCursor;
    else if(y >= _highlight->rect().y() - 2 && y <= _highlight->rect().y() + 2)
    {
      res = Qt::SizeBDiagCursor;
      _originY = true;
    }
    else if(res == Qt::ArrowCursor && (y >= _highlight->rect().y() + _highlight->rect().height() - 2 && y <= _highlight->rect().y() + _highlight->rect().height() + 2))
      res = Qt::SizeFDiagCursor;
    else if(res == Qt::ArrowCursor && (y >= _highlight->rect().y() - 2 && y <= _highlight->rect().y() + _highlight->rect().height() + 2))
      res = Qt::SizeHorCursor;
  }
  
  if(res == Qt::ArrowCursor && (y >= _highlight->rect().y() - 2 && y <= _highlight->rect().y() + 2 && x >= _highlight->rect().x() - 2 && x <= _highlight->rect().x() + _highlight->rect().width() + 2))
  {
    if(_ctrlPressed)
      res = Qt::SizeAllCursor;
    else
    {
      _originY = true;
      res = Qt::SizeVerCursor;
    }
  }
    
  if(res == Qt::ArrowCursor && (y >= _highlight->rect().y() + _highlight->rect().height()  - 2 && y <= _highlight->rect().y() + _highlight->rect().height() + 2 && x >= _highlight->rect().x() - 2 && x <= _highlight->rect().x() + _highlight->rect().width() + 2))
  {
    if(_ctrlPressed)
      res = Qt::SizeAllCursor;
    else
      res = Qt::SizeVerCursor;
  }
  
  _move = false;
  _resize = false;
  if(res == Qt::SizeAllCursor)
    _move = true;
  else if(res != Qt::ArrowCursor)
    _resize = true;
    
  return res;
}

void StandardImageView::ctrlPressed()
{
	_ctrlPressed = !_ctrlPressed;
}

void StandardImageView::showHighlightRect(const imagein::Rectangle* rect, ImageWindow* source)
{
	_highlight->setRect(((int)rect->x), ((int)rect->y), ((int)rect->w), ((int)rect->h));
  _originalHighlight->x = (int)rect->x;
  _originalHighlight->y = (int)rect->y;
  _originalHighlight->w = (int)rect->w;
  _originalHighlight->h = (int)rect->h;
  
  _selection->x = (int)rect->x;
  _selection->y = (int)rect->y;
  _selection->w = (int)rect->w;
  _selection->h = (int)rect->h;
  
  _vLine = (_originalHighlight->w == 0 && _originalHighlight->h == _image->getHeight());
  _hLine = (_originalHighlight->h == 0 && _originalHighlight->w == _image->getWidth());
  
  AlternativeImageView* view = source->getView();
  if(view != NULL && (_sourceHighlight = dynamic_cast<GenericHistogramView*>(view))) {}
  else _sourceHighlight = NULL;
}

void StandardImageView::selectAll()
{
  _sourceHighlight = NULL;
  _selection->x = 0;
  _selection->y = 0;
  _selection->w = _image->getWidth();
  _selection->h = _image->getHeight();
  
  _highlight->setRect(_selection->x, _selection->y, _selection->w, _selection->h);  
}

void StandardImageView::setImage(imagein::Image* image)
{
  _selection = new Rectangle(0, 0, image->getWidth(), image->getHeight());
  _visibleArea = new Rectangle(0, 0, image->getWidth(), image->getHeight());
    
	_zoomFactor = 1;
  
  _sourceHighlight = NULL;
  _originalHighlight = new Rectangle(0, 0, _image->getWidth(), _image->getHeight());
  _resize = false;
  _originX = false;
  _originY = false;
  _vLine = false;
  _hLine = false;
  
  _pixelClicked = new QPoint(-1, -1);
  
  QImage im(getQImage(image));

  //Qt ne peut pas afficher les QImage directement, on en fait un QPixmap...
  _pixmap_img = new QPixmap();
  _pixmap_img->convertFromImage(im);
    
  this->setPixmap(*_pixmap_img);
	//_scene->addItem(this);
	
	_highlight = new QGraphicsRectItem(((int)_selection->x), ((int)_selection->y), ((int)_selection->w), ((int)_selection->h));
	
	//_scene->addItem(_highlight);
	//_view->setScene(_scene);
  
  _image = image;
}


QImage genericinterface::getQImage(const imagein::Image* image) 
{
  QImage im(image->getWidth(), image->getHeight(), QImage::Format_ARGB32);

  //on récupère les bits de l'image qt, qu'on cast en QRgb (qui fait 32 bits -> une image RGBA)
  QRgb* data = reinterpret_cast<QRgb*>(im.bits());
  Image::const_iterator it = image->begin();
  
  for(unsigned int i = 0 ; i < image->getHeight()*image->getWidth() ; ++i)
  {
    //Pour chaque pixel de l'image Qt, on récupère les données correspondantes de l'image ImageIn grace à l'itérateur
    if(image->getNbChannels() == 4)
    {
      unsigned char red = *(it++);
      unsigned char green = *(it++);
      unsigned char blue = *(it++);
      unsigned char alpha = *(it++);

      //On utilise la fonction qRgba pour en faire un pointeur de qRgb
      data[i] = qRgba(red, green, blue, alpha);
    }
    else if(image->getNbChannels() == 3)
    {
      unsigned char red = *(it++);
      unsigned char green = *(it++);
      unsigned char blue = *(it++);

      //On utilise la fonction qRgba pour en faire un pointeur de qRgb
      data[i] = qRgb(red, green, blue);		
    }
    else if(image->getNbChannels() == 2)
    {
      unsigned char gray = *(it++);
      unsigned char alpha = *(it++);

      //On utilise la fonction qRgba pour en faire un pointeur de qRgb
      data[i] = qRgba(gray, gray, gray, alpha);		
    }
    else if(image->getNbChannels() == 1)
    {
      unsigned char gray = *(it++);

      //On utilise la fonction qRgba pour en faire un pointeur de qRgb
      data[i] = qRgb(gray, gray, gray);			
    }
  }
  return im;
}
