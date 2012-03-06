#include "StandardImageWindow.h"

using namespace genericinterface;
using namespace imagein;
using namespace std;

StandardImageWindow::StandardImageWindow(const QString & path, GenericInterface* gi): ImageWindow(), _gi(gi)
{
    _path = path;
    Image* im = new Image(path.toStdString());
    this->setWindowTitle("Image - " + path);
    _imageView = new StandardImageView(this, im);
	
    init();

    this->show();
}

#ifdef DEPRECIATE 

StandardImageWindow::StandardImageWindow(QMdiArea* area): ImageWindow(), _area(area)
{
    this->setWindowTitle("Image");
    _imageView = new StandardImageView(this);
	
	init();
	
    this->show();
}

StandardImageWindow::StandardImageWindow(QMdiArea* area, QString file): ImageWindow(), _area(area)
{
    this->setWindowTitle("Image");
	_imageView = new StandardImageView(this, file);
	
	init();
	
	this->show();
}

StandardImageWindow::StandardImageWindow(QMdiArea* area, Image* image): ImageWindow(), _area(area)
{
    this->setWindowTitle("Image - imageTitle");
    _imageView = new StandardImageView(this, image);
	
	init();

    this->show();
}

StandardImageWindow::StandardImageWindow(QMdiArea* area, Image* image, StandardImageWindow* source): ImageWindow(source), _area(area)
{
    this->setWindowTitle("Image - imageTitle");
    _imageView = new StandardImageView(this, image);
	
	init();

    this->show();
}

#endif

void StandardImageWindow::init()
{
	_selectedPixel = new QPoint();
	
	QScrollArea* scrollArea = new QScrollArea();
	scrollArea->setWidget(_imageView);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);
	
	initStatusBar();
    
	QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(scrollArea);
	layout->addWidget(_statusBar);
	this->setLayout(layout);
	
    connect(_imageView, SIGNAL(pixelClicked(int, int)), this, SLOT(showSelectedPixelInformations(int, int)));
    connect(_imageView, SIGNAL(pixelHovered(int, int)), this, SLOT(showHoveredPixelInformations(int, int)));
    connect(_imageView, SIGNAL(zoomChanged(double)), this, SLOT(updateZoom(double)));
    connect(this, SIGNAL(ctrlPressed()), _imageView, SLOT(ctrlPressed()));
}

void StandardImageWindow::showHistogram()
{
  list<HistogramWindow*> histos = getHistogram();

  for(list<HistogramWindow*>::iterator it = histos.begin(); it != histos.end(); ++it)
  {
    dynamic_cast<WindowService*>(_gi->getService(0))->addWidget(_path, *it);
  }
}

list<HistogramWindow*> StandardImageWindow::getHistogram()
{
  //Rectangle rect = _imageView->getRectangle();
  Rectangle rect;

  Image* im = _imageView->getImage();
  list<HistogramWindow*> histos;

  for(unsigned int i = 0; i < im->getNbChannels(); i++)
  {
    imagein::Histogram* h = new imagein::Histogram(*im, i, rect);
    HistogramWindow* histo = new HistogramWindow(im, this, h);
    
    std::ostringstream oss;
    oss << i;
    std::string is = oss.str();
    histo->setWindowTitle(QString::fromStdString("Histogram " + is));

    histos.push_back(histo);
  }

  return histos;
}

void StandardImageWindow::showPixelsGrid()
{
	GridWindow* grid = new GridWindow(_imageView->getImage(), this);
	_area->addSubWindow(grid);
	grid->show();
}

void StandardImageWindow::showLineProfile()
{
	std::cout << _selectedPixel->y() << std::endl;
	Image* im = _imageView->getImage();
	for(unsigned int i = 0; i < im->getNbChannels(); i++)
	{
		imagein::Histogram* h = new imagein::Histogram(*_imageView->getImage(), i, Rectangle(0, _selectedPixel->y(), im->getWidth(), _selectedPixel->y() + 1));
		RowWindow* histo = new RowWindow(_imageView->getImage(), this, h);
		
		std::ostringstream oss;
		oss << i;
		std::string is = oss.str();
		histo->setWindowTitle(QString::fromStdString("Line Profile " + is));
		
		_area->addSubWindow(histo);
		histo->show();
	}
}

void StandardImageWindow::showColumnProfile()
{
	std::cout << _selectedPixel->x() << std::endl;
	Image* im = _imageView->getImage();
	for(unsigned int i = 0; i < im->getNbChannels(); i++)
	{
		imagein::Histogram* h = new imagein::Histogram(*_imageView->getImage(), i, Rectangle(_selectedPixel->x(), 0, _selectedPixel->x() + 1, im->getHeight()));
		RowWindow* histo = new RowWindow(_imageView->getImage(), this, h, true);
		
		std::ostringstream oss;
		oss << i;
		std::string is = oss.str();
		histo->setWindowTitle(QString::fromStdString("Column Profile " + is));
		
		_area->addSubWindow(histo);
		histo->show();
	}
}

void StandardImageWindow::initStatusBar()
{
	std::ostringstream oss;
    oss << _imageView->getPixmap()->height();
    std::string height = oss.str();
    oss.str("");
    oss << _imageView->getPixmap()->width();
    std::string width = oss.str();
	
	QFont font;
    _statusBar = new QStatusBar();
    
    _lImageName = new QLabel("Name: Nom_Image");
    font = _lImageName->font();
    font.setPointSize(8);
    font.setBold(true);
    _lImageName->setFont(font);
    
    _lImageSize = new QLabel(QString::fromStdString("(" + width + " * " + height + ")"));
    font = _lImageSize->font();
    font.setPointSize(8);
    _lImageSize->setFont(font);
    
    _lSelectedPixelInfo = new QLabel("Selected: ");
    font = _lSelectedPixelInfo->font();
    font.setPointSize(8);
    font.setBold(true);
    _lSelectedPixelInfo->setFont(font);
    
    _lSelectedPixelPosition = new QLabel("");
    font = _lSelectedPixelPosition->font();
    font.setPointSize(8);
    _lSelectedPixelPosition->setFont(font);
    
    _lSelectedPixelColor = new QLabel("Color: ");
    font = _lSelectedPixelColor->font();
    font.setPointSize(8);
    _lSelectedPixelColor->setFont(font);
    
    _lHoveredPixelInfo = new QLabel("Hovered: ");
    font = _lHoveredPixelInfo->font();
    font.setBold(true);
    font.setPointSize(8);
    _lHoveredPixelInfo->setFont(font);
    
    _lHoveredPixelPosition = new QLabel("");
    font = _lHoveredPixelPosition->font();
    font.setPointSize(8);
    _lHoveredPixelPosition->setFont(font);
    
    _lHoveredPixelColor = new QLabel("Color: ");
    font = _lHoveredPixelColor->font();
    font.setPointSize(8);
    _lHoveredPixelColor->setFont(font);
    
    _lZoom = new QLabel("Zoom: 100%");
    font = _lZoom->font();
    font.setPointSize(8);
    _lZoom->setFont(font);

	_statusBar->addWidget(_lImageName);
    _statusBar->addWidget(_lImageSize);
	_statusBar->addWidget(_lSelectedPixelInfo);
	_statusBar->addWidget(_lSelectedPixelPosition);
	_statusBar->addWidget(_lSelectedPixelColor);
	_statusBar->addWidget(_lHoveredPixelInfo);
	_statusBar->addWidget(_lHoveredPixelPosition);
	_statusBar->addWidget(_lHoveredPixelColor);
	_statusBar->addWidget(_lZoom);
}

void StandardImageWindow::showSelectedPixelInformations(int x, int y)
{
	_selectedPixel->setX(x);
	_selectedPixel->setY(y);
	std::ostringstream oss;
    oss << x;
    std::string xs = oss.str();
    oss.str("");
    oss << y;
    std::string ys = oss.str();
	_lSelectedPixelPosition->setText(QString::fromStdString(xs + " * " + ys));
}

void StandardImageWindow::showHoveredPixelInformations(int x, int y)
{
	std::ostringstream oss;
    oss << x;
    std::string xs = oss.str();
    oss.str("");
    oss << y;
    std::string ys = oss.str();
	_lHoveredPixelPosition->setText(QString::fromStdString(xs + " * " + ys));
}

void StandardImageWindow::updateZoom(double z)
{
	std::ostringstream oss;
    oss << z;
    std::string zs = oss.str();
	_lZoom->setText(QString::fromStdString("Zoom: " + zs + "%"));
}

void StandardImageWindow::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Control)
		emit ctrlPressed();
}

void StandardImageWindow::keyReleaseEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Control)
		emit ctrlPressed();
}
