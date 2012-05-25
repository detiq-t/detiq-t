#include "GenericHistogramView.h"

using namespace genericinterface;
using namespace imagein;

GenericHistogramView::GenericHistogramView(const Image* image, imagein::Rectangle* rect, bool horizontal, int value, bool projection): AlternativeImageView(image), _rectangle(rect), _horizontal(horizontal), _value(value), _projection(projection)
{
	_qwtPlot = new QwtPlot();
	init();
}

GenericHistogramView::~GenericHistogramView()
{
	delete _principalPicker;
	delete _leftPicker;
	delete _rightPicker;
}

void GenericHistogramView::init()
{
  this->setMouseTracking(true); //Switch on mouse tracking (no need to press button)

  _qwtPlot->setTitle("Histogram");
  
  _qwtPlot->setCanvasBackground(QColor(Qt::gray));
  _qwtPlot->plotLayout()->setAlignCanvasToScales(true);

  _qwtPlot->setAxisTitle(QwtPlot::yLeft, "Number of specimen");
  _qwtPlot->setAxisTitle(QwtPlot::xBottom, "Pixel value");

	QwtLegend* legend = new QwtLegend();
  legend->setItemMode(QwtLegend::CheckableItem);
  _qwtPlot->insertLegend(legend, QwtPlot::RightLegend);

  populate();
  
  _qwtPlot->canvas()->setMouseTracking(true);
  
  if(_horizontal)
  _principalPicker = new HistogramPicker(QwtPlotPicker::HLineRubberBand, QwtPicker::AlwaysOn, _qwtPlot->canvas());
  else
  _principalPicker = new HistogramPicker(QwtPlotPicker::VLineRubberBand, QwtPicker::AlwaysOn, _qwtPlot->canvas());
  _principalPicker->setStateMachine(new QwtPickerDragPointMachine());
  _principalPicker->setTrackerPen(QColor(Qt::white));
  _principalPicker->setRubberBandPen(QColor(Qt::yellow));
  
  _leftPicker = new HistogramPicker(_qwtPlot->canvas());
  _leftPicker->setStateMachine(new QwtPickerDragPointMachine());
  
  _rightPicker = new HistogramPicker(_qwtPlot->canvas());
  _rightPicker->setStateMachine(new QwtPickerDragPointMachine());
  _rightPicker->setRubberBand(QwtPlotPicker::VLineRubberBand);
  _rightPicker->setRubberBandPen(QColor(Qt::yellow));
	_rightPicker->setMousePattern(QwtPicker::MouseSelect1, Qt::RightButton);

  connect(_qwtPlot, SIGNAL(legendChecked(QwtPlotItem*, bool)), this, SLOT(showItem(QwtPlotItem*, bool)));
  connect(_rightPicker, SIGNAL(selected(const QPointF&)), this, SLOT(rightClick(const QPointF&)));
  connect(_leftPicker, SIGNAL(selected(const QPointF&)), this, SLOT(leftClick(const QPointF&)));
  connect(_principalPicker, SIGNAL(moved(const QPointF&)), this, SLOT(move(const QPointF&)));

  _qwtPlot->replot(); // creating the legend items

  QwtPlotItemList items = _qwtPlot->itemList(QwtPlotItem::Rtti_PlotHistogram);
  for(int i = 0; i < items.size(); i++)
  {
      QwtLegendItem* legendItem = qobject_cast<QwtLegendItem*>(legend->find(items[i]));
      if(legendItem)
    legendItem->setChecked(true);

  items[i]->setVisible(true);
  }

  _qwtPlot->setAutoReplot(true);
}

void GenericHistogramView::populate()
{
  QwtPlotGrid* grid = new QwtPlotGrid();
  grid->enableX(false);
  grid->enableY(true);
  grid->enableXMin(false);
  grid->enableYMin(false);
  grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));
  grid->attach(_qwtPlot);

	for(unsigned int i = 0; i < _image->getNbChannels(); ++i)
	{
		imagein::Array<unsigned int>* histogram;
		if(_projection)
			histogram = new imagein::ProjectionHistogram(*_image, _value, _horizontal, *_rectangle, i);
		else
			histogram = new imagein::Histogram(*_image, i, *_rectangle);
		
		int values[histogram->getWidth()];

		for(unsigned int j = 0; j < histogram->getWidth(); ++j)
			values[j] = (*histogram)[j];
		
		GraphicalHistogram* graphicalHisto;
		switch(i)
		{
			case 0:
				if(_image->getNbChannels() == 1 || _image->getNbChannels() == 2)
					graphicalHisto = new GraphicalHistogram("Black", Qt::black);
				else
					graphicalHisto = new GraphicalHistogram("Red", Qt::red);
			break;
			case 1:
				if(_image->getNbChannels() == 1 || _image->getNbChannels() == 2)
					graphicalHisto = new GraphicalHistogram("Alpha", Qt::white);
				else
					graphicalHisto = new GraphicalHistogram("Green", Qt::green);
			break;
			case 2:
				graphicalHisto = new GraphicalHistogram("Blue", Qt::blue);
			break;
			case 3:
				graphicalHisto = new GraphicalHistogram("Alpha", Qt::black);
			break;
			default:
				graphicalHisto = new GraphicalHistogram("Default", Qt::black);
		}
		graphicalHisto->setValues(sizeof(values) / sizeof(int), values);
		if(_horizontal)
			graphicalHisto->setOrientation(Qt::Horizontal);
		graphicalHisto->attach(_qwtPlot);
    _graphicalHistos.push_back(graphicalHisto);
	}
}

void GenericHistogramView::update(const imagein::Rectangle* rect)
{
  _rectangle->x = rect->x;
  _rectangle->y = rect->y;
  _rectangle->w = rect->w;
  _rectangle->h = rect->h;
  
  emit(updateApplicationArea(rect));
  
  for(unsigned int i = 0; i < _image->getNbChannels(); ++i)
	{
		imagein::Array<unsigned int>* histogram;
		if(_projection)
			histogram = new imagein::ProjectionHistogram(*_image, _value, _horizontal, *_rectangle, i);
		else
			histogram = new imagein::Histogram(*_image, i, *_rectangle);
		
		int values[histogram->getWidth()];

		for(unsigned int j = 0; j < histogram->getWidth(); ++j)
			values[j] = (*histogram)[j];
		
		_graphicalHistos[i]->setValues(sizeof(values) / sizeof(int), values);
	}
}

void GenericHistogramView::showItem(QwtPlotItem *item, bool on) const
{
  item->setVisible(on);
}

void GenericHistogramView::leftClick(const QPointF& pos) const
{
  emit(leftClickedValue((int)pos.x()));
}

void GenericHistogramView::rightClick(const QPointF& pos) const
{
  emit(rightClickedValue((int)pos.x()));
}

void GenericHistogramView::move(const QPointF& pos) const
{
	emit(hoveredValue((int)pos.x()));
}
