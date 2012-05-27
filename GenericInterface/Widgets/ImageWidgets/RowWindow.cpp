#include "RowWindow.h"

using namespace genericinterface;
using namespace imagein;

RowWindow::RowWindow(const imagein::Image* image, imagein::Rectangle* rect, const QString path, GenericInterface *gi, const ImageWindow* source, bool vertical): ImageWindow(path, source, rect), _gi(gi)
{
	_view = new RowView(image, rect);
	if(vertical)
        this->setWindowTitle(ImageWindow::getTitleFromPath(_path) + QString::fromStdString(" - Column Profile"));
	else
        this->setWindowTitle(ImageWindow::getTitleFromPath(_path) + QString::fromStdString(" - Line Profile"));
	
	init();
}

RowWindow::~RowWindow()
{
	delete _view;
}

void RowWindow::init()
{
	QScrollArea* scrollArea = new QScrollArea();
	scrollArea->setWidget(_view);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);
	
	initStatusBar();
	
	QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_view->getGraphicalHistogram());
	layout->addWidget(_statusBar);
	this->setLayout(layout);
	
    connect(_view, SIGNAL(leftClickedValue(int)), this, SLOT(showLeftClickedValue(int)));
    connect(_view, SIGNAL(rightClickedValue(int)), this, SLOT(showRightClickedValue(int)));
    connect(_view, SIGNAL(hoveredValue(int)), this, SLOT(showHoveredValue(int)));	
	
	this->show();
}

void RowWindow::initStatusBar()
{
	QFont font;
    _statusBar = new QStatusBar();
    
    _lImageName = new QLabel(QString::fromStdString("Image: ") + ImageWindow::getTitleFromPath(_path));
    font = _lImageName->font();
    font.setPointSize(8);
    font.setBold(true);
    _lImageName->setFont(font);
    
    _lHoveredValue = new QLabel("Hovered Value: ");
    font = _lHoveredValue->font();
    font.setPointSize(8);
    _lHoveredValue->setFont(font);
    
    _lSelectedValue1 = new QLabel("Value1: ");
    font = _lSelectedValue1->font();
    font.setPointSize(8);
    _lSelectedValue1->setFont(font);
    
    _lSelectedValue2 = new QLabel("Value2: ");
    font = _lSelectedValue2->font();
    font.setPointSize(8);
    _lSelectedValue2->setFont(font);

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
    QWidget* widget = new QWidget();
	
	QHBoxLayout* layout1 = new QHBoxLayout();
	layout1->setContentsMargins(0, 0, 0, 0);
    QWidget* widget1 = new QWidget();
	layout1->addWidget(_lImageName);
	layout1->addSpacing(15);
	layout1->addWidget(_lHoveredValue);
    widget1->setLayout(layout1);
    layout->addWidget(widget1);
	
	QHBoxLayout* layout2 = new QHBoxLayout();
	layout2->setContentsMargins(0, 0, 0, 0);
    QWidget* widget2 = new QWidget();
	layout2->addWidget(_lSelectedValue1);
	layout2->addSpacing(15);
	layout2->addWidget(_lSelectedValue2);
    widget2->setLayout(layout2);
    layout->addWidget(widget2);
    
    widget->setLayout(layout);
	
    _statusBar->addWidget(widget);
}

void RowWindow::showHoveredValue(int value) const
{
	std::ostringstream oss;
    oss << value;
    std::string xs = oss.str();
	_lHoveredValue->setText(QString::fromStdString("Hovered: " + xs + "\t") + valueFromHistogram(value));
}

void RowWindow::showLeftClickedValue(int value) const
{
	std::ostringstream oss;
    oss << value;
    std::string xs = oss.str();
	_lHoveredValue->setText(QString::fromStdString("Value1: " + xs + "\t") + valueFromHistogram(value));
}

void RowWindow::showRightClickedValue(int value) const
{
	std::ostringstream oss;
    oss << value;
    std::string xs = oss.str();
	_lHoveredValue->setText(QString::fromStdString("Value2: " + xs + "\t") + valueFromHistogram(value));
}

QString RowWindow::valueFromHistogram(unsigned int value) const
{
	std::ostringstream oss;
	QString s = QString("");

  bool out = false;
    if(value > 255)
    out = true;
  
  for(unsigned int i = 0; i < _view->getImage()->getNbChannels(); ++i)
  {
    int n = out ? 0 : (*(_view->getHistogram(i)))[value];
    oss.str("");
    oss << n;
    
    if(_view->getImage()->getNbChannels() == 1)
    {
      if(i == 0)
        s += QString::fromStdString(" C: " + oss.str());		
    }
    else if(_view->getImage()->getNbChannels() == 2)
    {
      if(i == 0)
        s += QString::fromStdString(" C: " + oss.str());
      else if(i == 1)
        s += QString::fromStdString(" A: " + oss.str());			
    }
    else if(_view->getImage()->getNbChannels() >= 3)
    {
      if(i == 0)
        s += QString::fromStdString(" R: " + oss.str());
      else if(i == 1)
        s += QString::fromStdString(" G: " + oss.str());
      else if(i == 2)
        s += QString::fromStdString(" B: " + oss.str());
      else if(i == 3)
        s += QString::fromStdString(" A: " + oss.str());
    }
  }
    
	return s;
}
