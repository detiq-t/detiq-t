#include "RowWindow.h"

using namespace genericinterface;
using namespace imagein;

RowWindow::RowWindow(imagein::Image* image, imagein::Rectangle* rect, const QString& path, GenericInterface *gi, ImageWindow* source, bool vertical): ImageWindow(source, rect)
{
  _path = path;
  _gi = gi;

	_view = new RowView(image, rect);
	if(vertical)
		this->setWindowTitle("Column Profile - imageTitle");
	else
		this->setWindowTitle("Line Profile - imageTitle");
	
	init();
	
	this->show();
}

void RowWindow::init()
{
	QScrollArea* scrollArea = new QScrollArea();
	scrollArea->setWidget(_view);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setAlignment(Qt::AlignCenter);
	
	initStatusBar();
	
	QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(_view->getHistogram());
	layout->addWidget(_statusBar);
	this->setLayout(layout);
	
    connect(_view, SIGNAL(valueClickedLeft(int)), this, SLOT(showLeftClickedValue(int)));
    connect(_view, SIGNAL(valueClickedRight(int)), this, SLOT(showRightClickedValue(int)));
    connect(_view, SIGNAL(valueHovered(int)), this, SLOT(showHoveredValue(int)));	
}

void RowWindow::initStatusBar()
{
	QFont font;
    _statusBar = new QStatusBar();
    
    _lImageName = new QLabel("Image: Nom_Image");
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

void RowWindow::showHoveredValue(int value)
{
	std::ostringstream oss;
    oss << value;
    std::string xs = oss.str();
	_lHoveredValue->setText(QString::fromStdString("Hovered: " + value));
}

void RowWindow::showLeftClickedValue(int value)
{
	std::ostringstream oss;
    oss << value;
    std::string xs = oss.str();
	_lHoveredValue->setText(QString::fromStdString("Value1: " + value));
}

void RowWindow::showRightClickedValue(int value)
{
	std::ostringstream oss;
    oss << value;
    std::string xs = oss.str();
	_lHoveredValue->setText(QString::fromStdString("Value2: " + value));
}
