#include "GridWindow.h"

using namespace genericinterface;

GridWindow::GridWindow(Image* image, StandardImageWindow* source): ImageWindow(source)
{
	_view = new GridView(image);
	this->setWindowTitle("Pixels Grid - imageTitle");
	
	init();
	
	this->show();
}

void GridWindow::init()
{
	/*QScrollArea* scrollArea = new QScrollArea();
	scrollArea->setWidget(_view->getGraphicsView());
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);*/
	
	initStatusBar();
	
	QVBoxLayout* layout = new QVBoxLayout();
	
    layout->addWidget(_view->getGraphicsView());
	layout->addWidget(_statusBar);
	this->setLayout(layout);
	
    connect(_view, SIGNAL(pixelClickedLeft(int, int)), this, SLOT(showLeftClickedPixel(int, int)));
    connect(_view, SIGNAL(pixelClickedRight(int, int)), this, SLOT(showRightClickedPixel(int, int)));
    connect(_view, SIGNAL(pixelHovered(int, int)), this, SLOT(showHoveredPixel(int, int)));
}

void GridWindow::initStatusBar()
{
	QFont font;
    _statusBar = new QStatusBar();
    
    _lImageName = new QLabel("Image: Nom_Image");
    font = _lImageName->font();
    font.setPointSize(8);
    font.setBold(true);
    _lImageName->setFont(font);
    
    _lHoveredPixelInfo = new QLabel("Hovered: ");
    font = _lHoveredPixelInfo->font();
    font.setPointSize(8);
    font.setBold(true);
    _lHoveredPixelInfo->setFont(font);
    
    _lSelectedPixel1Info = new QLabel("Pixel1: ");
    font = _lSelectedPixel1Info->font();
    font.setPointSize(8);
    font.setBold(true);
    _lSelectedPixel1Info->setFont(font);
    
    _lSelectedPixel2Info = new QLabel("Pixel2: ");
    font = _lSelectedPixel2Info->font();
    font.setPointSize(8);
    font.setBold(true);
    _lSelectedPixel2Info->setFont(font);
    
    _lHoveredPixelPosition = new QLabel("");
    font = _lHoveredPixelPosition->font();
    font.setPointSize(8);
    _lHoveredPixelPosition->setFont(font);
    
    _lSelectedPixel1Position = new QLabel("");
    font = _lSelectedPixel1Position->font();
    font.setPointSize(8);
    _lSelectedPixel1Position->setFont(font);
    
    _lSelectedPixel2Position = new QLabel("");
    font = _lSelectedPixel2Position->font();
    font.setPointSize(8);
    _lSelectedPixel2Position->setFont(font);
    
    _lHoveredPixelColor = new QLabel("Color: ");
    font = _lHoveredPixelColor->font();
    font.setPointSize(8);
    _lHoveredPixelColor->setFont(font);
    
    _lSelectedPixel1Color = new QLabel("Color: ");
    font = _lSelectedPixel1Color->font();
    font.setPointSize(8);
    _lSelectedPixel1Color->setFont(font);
    
    _lSelectedPixel2Color = new QLabel("Color: ");
    font = _lSelectedPixel2Color->font();
    font.setPointSize(8);
    _lSelectedPixel2Color->setFont(font);

	_statusBar->addWidget(_lImageName);
	_statusBar->addWidget(_lHoveredPixelInfo);
	_statusBar->addWidget(_lHoveredPixelPosition);
	_statusBar->addWidget(_lHoveredPixelColor);
	_statusBar->addWidget(_lSelectedPixel1Info);
	_statusBar->addWidget(_lSelectedPixel1Position);
	_statusBar->addWidget(_lSelectedPixel1Color);
	_statusBar->addWidget(_lSelectedPixel2Info);
	_statusBar->addWidget(_lSelectedPixel2Position);
	_statusBar->addWidget(_lSelectedPixel2Color);
}

void GridWindow::showHoveredPixel(int x, int y)
{
	std::ostringstream oss;
    oss << x;
    std::string xs = oss.str();
    oss.str("");
    oss << y;
    std::string ys = oss.str();
	_lHoveredPixelPosition->setText(QString::fromStdString(xs + " * " + ys));
}

void GridWindow::showLeftClickedPixel(int x, int y)
{
	std::ostringstream oss;
    oss << x;
    std::string xs = oss.str();
    oss.str("");
    oss << y;
    std::string ys = oss.str();
	_lSelectedPixel1Position->setText(QString::fromStdString(xs+ " * " + ys));
}

void GridWindow::showRightClickedPixel(int x, int y)
{
	std::ostringstream oss;
    oss << x;
    std::string xs = oss.str();
    oss.str("");
    oss << y;
    std::string ys = oss.str();
	_lSelectedPixel2Position->setText(QString::fromStdString(xs + " * " + ys));
}
