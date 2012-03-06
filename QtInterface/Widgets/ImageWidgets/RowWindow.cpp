#include "RowWindow.h"

using namespace genericinterface;
using namespace imagein;

RowWindow::RowWindow(Image* image, ImageWindow* source, Histogram* histogram, bool vertical): ImageWindow(source)
{
	_view = new RowView(image, histogram);
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
    
	_statusBar->addWidget(_lImageName);    
	_statusBar->addWidget(_lHoveredValue);
	_statusBar->addWidget(_lSelectedValue1);
	_statusBar->addWidget(_lSelectedValue2);
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
