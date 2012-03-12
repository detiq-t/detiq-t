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
	_isRootImage = false;

	init();
	
	this->show();
}


void StandardImageWindow::init()
{
  _selectedPixel = new QPoint();
  
  initStatusBar();

  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(_imageView->getGraphicsView());
  layout->addWidget(_statusBar);
  this->setLayout(layout);
	
  QObject::connect(_imageView, SIGNAL(pixelClicked(int, int)), this, SLOT(showSelectedPixelInformations(int, int)));
  QObject::connect(_imageView, SIGNAL(pixelHovered(int, int)), this, SLOT(showHoveredPixelInformations(int, int)));
  QObject::connect(_imageView, SIGNAL(zoomChanged(double)), this, SLOT(updateZoom(double)));
  QObject::connect(this, SIGNAL(ctrlPressed()), _imageView, SLOT(ctrlPressed()));
  QObject::connect(this, SIGNAL(highlightRectChange(imagein::Rectangle*)), _imageView, SLOT(showHighlightRect(imagein::Rectangle*)));
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
  Image* im = _imageView->getImage();
  list<HistogramWindow*> histos;

  HistogramWindow* histo = new HistogramWindow(im, _imageView->getRectangle(), this);
  histos.push_back(histo);

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
	Image* im = _imageView->getImage();
	imagein::Rectangle* rect = new Rectangle(0, _selectedPixel->y(), im->getWidth(), 1);
	RowWindow* histo = new RowWindow(im, rect, _path, _gi, this);

	dynamic_cast<WindowService*>(_gi->getService(0))->addWidget(_path, histo);
}

void StandardImageWindow::showColumnProfile()
{
	Image* im = _imageView->getImage();
	imagein::Rectangle* rect = new Rectangle(_selectedPixel->x(), 0, 1, im->getHeight());
	RowWindow* histo = new RowWindow(im, rect, _path, _gi, this, true);

	dynamic_cast<WindowService*>(_gi->getService(0))->addWidget(_path, histo);
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


	QVBoxLayout* layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
    QWidget* widget = new QWidget();
	
	QHBoxLayout* layoutImage = new QHBoxLayout();
	layoutImage->setContentsMargins(0, 0, 0, 0);
    QWidget* widgetImage = new QWidget();
	layoutImage->addWidget(_lImageName);
    layoutImage->addWidget(_lImageSize);
	layoutImage->addSpacing(15);
	layoutImage->addWidget(_lZoom);
    widgetImage->setLayout(layoutImage);
    layout->addWidget(widgetImage);
	
	QHBoxLayout* layoutSelectedPixel = new QHBoxLayout();
	layoutSelectedPixel->setContentsMargins(0, 0, 0, 0);
    QWidget* widgetSelectedPixel = new QWidget();
	layoutSelectedPixel->addWidget(_lSelectedPixelInfo);
    layoutSelectedPixel->addWidget(_lSelectedPixelPosition);
    layoutSelectedPixel->addWidget(_lSelectedPixelColor);
    widgetSelectedPixel->setLayout(layoutSelectedPixel);
    layout->addWidget(widgetSelectedPixel);
	
	QHBoxLayout* layoutHoveredPixel = new QHBoxLayout();
	layoutHoveredPixel->setContentsMargins(0, 0, 0, 0);
    QWidget* widgetHoveredPixel = new QWidget();
	layoutHoveredPixel->addWidget(_lHoveredPixelInfo);
    layoutHoveredPixel->addWidget(_lHoveredPixelPosition);
    layoutHoveredPixel->addWidget(_lHoveredPixelColor);
    widgetHoveredPixel->setLayout(layoutHoveredPixel);
    layout->addWidget(widgetHoveredPixel);    
    
    widget->setLayout(layout);
	
    _statusBar->addWidget(widget);
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
	
	_lSelectedPixelColor->setText("Color:");
	Image* im = _imageView->getImage();
	for(unsigned int i = 0; i < im->getNbChannels(); i++)
	{
		oss.str("");
		oss << (unsigned int) im->getPixel(x, y, i);
		_lSelectedPixelColor->setText(_lSelectedPixelColor->text() + QString::fromStdString(" " + oss.str()));
	}
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
	
	_lHoveredPixelColor->setText("Color:");
	Image* im = _imageView->getImage();
	for(unsigned int i = 0; i < im->getNbChannels(); i++)
	{
		oss.str("");
		oss << (unsigned int) im->getPixel(x, y, i);
		_lHoveredPixelColor->setText(_lHoveredPixelColor->text() + QString::fromStdString(" " + oss.str()));
	}
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

void StandardImageWindow::showHighlightRect(Rectangle* rect)
{
	emit(highlightRectChange(rect));
}

void StandardImageWindow::setAsRoot()
{
  _isRootImage = true;
}

void StandardImageWindow::closeEvent(QCloseEvent* event)
{
  if (_isRootImage)
  {
    int answer = QMessageBox::question(this, "Attention", "You're going to close all the relative windows, are you sure you want to continue?", QMessageBox::Yes | QMessageBox::No);
	 if (answer == QMessageBox::Yes)
	 {
	   event->accept();
    }
	 else
	   event->ignore();
  }
  else
    event->accept();  // if the image isn't a root image we can close it without quastion
}
