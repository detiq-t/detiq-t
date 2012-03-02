#include "StandardImageWindow.h"

using namespace genericinterface;

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

void StandardImageWindow::init()
{
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

void StandardImageWindow::showHistogram(Rectangle* rect)
{
	Image* im = _imageView->getImage();
	for(unsigned int i = 0; i < im->getNbChannels(); i++)
	{
		HistogramWindow* histo = new HistogramWindow(_imageView->getImage(), this, im->getHistogram(i, *rect));
		_area->addSubWindow(histo);
		histo->show();
	}
}

void StandardImageWindow::showPixelsGrid()
{
	GridWindow* grid = new GridWindow();
	_area->addSubWindow(grid);
	grid->show();
}

void StandardImageWindow::showLineProfile()
{
	RowWindow* row = new RowWindow();
	_area->addSubWindow(row);
	row->show();
}

void StandardImageWindow::showColumnProfile()
{
	RowWindow* column = new RowWindow(true);
	_area->addSubWindow(column);
	column->show();
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
