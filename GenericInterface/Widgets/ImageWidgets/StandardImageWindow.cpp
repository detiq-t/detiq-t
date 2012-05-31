#include "StandardImageWindow.h"

#include <QPushButton>

using namespace genericinterface;
using namespace imagein;
using namespace std;

StandardImageWindow::StandardImageWindow(const QString path, GenericInterface* gi): ImageWindow(path), _gi(gi)
{
    _image = new Image(path.toStdString());
    this->setWindowTitle(ImageWindow::getTitleFromPath(path));

    _imageView = new StandardImageView(this, _image);
    init();
}

StandardImageWindow::StandardImageWindow(const QString path, GenericInterface* gi, Image* image): ImageWindow(path), _gi(gi)
{
    _image = image;

    this->setWindowTitle(ImageWindow::getTitleFromPath(path));

    _imageView = new StandardImageView(this, _image);

    init();
}

StandardImageWindow::~StandardImageWindow()
{
	delete _imageView;
  delete _selectedPixel;
  delete _image;
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
	QObject::connect(this, SIGNAL(highlightRectChange(const imagein::Rectangle*, ImageWindow*)), _imageView, SLOT(showHighlightRect(const imagein::Rectangle*, ImageWindow*)));

	this->show();
}

void StandardImageWindow::showHistogram()
{
    QString path = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE))->getWidgetId(this);
    const Image* im = _imageView->getImage();
    HistogramWindow* histo = new HistogramWindow(path, im, _imageView->getRectangle(), this);

    AlternativeImageView* view = histo->getView();
    GenericHistogramView* source;
    if(view != NULL && (source = dynamic_cast<GenericHistogramView*>(view)))
        QObject::connect(source, SIGNAL(updateApplicationArea(const imagein::Rectangle*)), histo, SLOT(setApplicationArea(const imagein::Rectangle*)));
        QObject::connect(histo, SIGNAL(highlightRectChange(const imagein::Rectangle*, ImageWindow*)), this, SLOT(showHighlightRect(const imagein::Rectangle*, ImageWindow*)));
   
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    QString id = ws->getWidgetId(this);
    ws->addWidget(id, histo);
}

void StandardImageWindow::showHProjectionHistogram()
{
    QString path = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE))->getWidgetId(this);
    const Image* im = _imageView->getImage();

    bool ok;
    int value = QInputDialog::getInt(this, "Select value", "What Value (0..255)?", 0, 0, 255, 1, &ok);

    if (ok)
    {
        ProjectionHistogramWindow* histo = new ProjectionHistogramWindow(path, im, _imageView->getRectangle(), this, value);

        AlternativeImageView* view = histo->getView();
        GenericHistogramView* source;
        if (view != NULL && (source = dynamic_cast<GenericHistogramView*>(view)))
            QObject::connect(source, SIGNAL(updateApplicationArea(const imagein::Rectangle*)), histo, SLOT(setApplicationArea(const imagein::Rectangle*)));

        WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
        QString id = ws->getWidgetId(this);
        ws->addWidget(id, histo);
    }
}

void StandardImageWindow::showVProjectionHistogram()
{
    QString path = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE))->getWidgetId(this);
    const Image* im = _imageView->getImage();
	
	bool ok;
	int value = QInputDialog::getInt(this, "Select value", "What Value (0..255)?", 0, 0, 255, 1, &ok);
	
	if(ok)
	{
        ProjectionHistogramWindow* histo = new ProjectionHistogramWindow(path, im, _imageView->getRectangle(), this, value, false);
    
		AlternativeImageView* view = histo->getView();
		GenericHistogramView* source;
		if (view != NULL && (source = dynamic_cast<GenericHistogramView*>(view)))
			QObject::connect(source, SIGNAL(updateApplicationArea(const imagein::Rectangle*)), histo, SLOT(setApplicationArea(const imagein::Rectangle*)));

        WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
        QString id = ws->getWidgetId(this);
        ws->addWidget(id, histo);
	} 
}

void StandardImageWindow::showPixelsGrid()
{
 
    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    QString id = ws->getWidgetId(this);
    GridWindow* grid = new GridWindow(id, _imageView->getImage(), this);
    ws->addWidget(id, grid);
}

void StandardImageWindow::showLineProfile()
{
    QString path = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE))->getWidgetId(this);

	const Image* im = _imageView->getImage();
	imagein::Rectangle* rect = new Rectangle(0, _selectedPixel->y(), im->getWidth(), 0);
    RowWindow* histo = new RowWindow(im, rect, path, _gi, this);
    
	AlternativeImageView* view = histo->getView();
	GenericHistogramView* source;
	if (view != NULL && (source = dynamic_cast<GenericHistogramView*>(view)))
		QObject::connect(source, SIGNAL(updateApplicationArea(const imagein::Rectangle*)), histo, SLOT(setApplicationArea(const imagein::Rectangle*)));

    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    QString id = ws->getWidgetId(this);
    ws->addWidget(id, histo);
}

void StandardImageWindow::showColumnProfile()
{
    QString path = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE))->getWidgetId(this);

    const Image* im = _imageView->getImage();
	imagein::Rectangle* rect = new Rectangle(_selectedPixel->x(), 0, 0, im->getHeight());
    RowWindow* histo = new RowWindow(im, rect, path, _gi, this, true);
    
	AlternativeImageView* view = histo->getView();
	GenericHistogramView* source;
	if (view != NULL && (source = dynamic_cast<GenericHistogramView*>(view)))
		QObject::connect(source, SIGNAL(updateApplicationArea(const imagein::Rectangle*)), histo, SLOT(setApplicationArea(const imagein::Rectangle*)));

    WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
    QString id = ws->getWidgetId(this);
    ws->addWidget(id, histo);
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

  _lImageName = new QLabel(QString::fromStdString("Image: ") + ImageWindow::getTitleFromPath(_path));
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

  QPushButton* bSelectAll = new QPushButton("Select All");
  QObject::connect(bSelectAll, SIGNAL(clicked()), _imageView, SLOT(selectAll()));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
  QWidget* widget = new QWidget();
	
	QHBoxLayout* layoutImage = new QHBoxLayout();
	layoutImage->setContentsMargins(0, 0, 0, 0);
  QWidget* widgetImage = new QWidget();
	layoutImage->addWidget(_lImageName);
  layoutImage->addWidget(_lImageSize);
	layoutImage->addSpacing(30);
	layoutImage->addWidget(_lZoom);
	layoutImage->addSpacing(30);
	layoutImage->addWidget(bSelectAll);
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

void StandardImageWindow::showSelectedPixelInformations(int x, int y) const
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
	const Image* im = _imageView->getImage();
	for(unsigned int i = 0; i < im->getNbChannels(); i++)
	{
		oss.str("");
		oss << (unsigned int) im->getPixel(x, y, i);
		_lSelectedPixelColor->setText(_lSelectedPixelColor->text() + QString::fromStdString(" " + oss.str()));
	}
}

void StandardImageWindow::showHoveredPixelInformations(int x, int y) const
{
	std::ostringstream oss;
    oss << x;
    std::string xs = oss.str();
    oss.str("");
    oss << y;
    std::string ys = oss.str();
	_lHoveredPixelPosition->setText(QString::fromStdString(xs + " * " + ys));
	
	_lHoveredPixelColor->setText("Color:");
	const Image* im = _imageView->getImage();
	for(unsigned int i = 0; i < im->getNbChannels(); i++)
	{
		oss.str("");
		try {
			oss << (unsigned int) im->getPixel(x, y, i);
		}
		catch(std::out_of_range&) {
		}
		_lHoveredPixelColor->setText(_lHoveredPixelColor->text() + QString::fromStdString(" " + oss.str()));
	}
}

void StandardImageWindow::updateZoom(double z) const
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

void StandardImageWindow::showHighlightRect(const Rectangle* rect, ImageWindow* source)
{
	emit(highlightRectChange(rect, source));
}

const imagein::Image* StandardImageWindow::getImage()
{
  return _imageView->getImage();
}

void StandardImageWindow::setImage(Image* image)
{
    _imageView->setImage(image);
    delete _image;
    _image = image;
}

const imagein::Rectangle* StandardImageWindow::getSelection()
{
  return _imageView->getRectangle();
}
