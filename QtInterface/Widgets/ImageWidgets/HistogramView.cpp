#include "HistogramView.h"

using namespace genericinterface;
using namespace imagein;

HistogramView::HistogramView(Image* image, imagein::Rectangle* rect): AlternativeImageView(image), _rectangle(rect)
{
	_qwtPlot = new QwtPlot();
	
	init();
}

void HistogramView::init()
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
    
    _qwtLeftPicker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, _qwtPlot->canvas());
    _qwtLeftPicker->setStateMachine(new QwtPickerDragPointMachine());
    _qwtLeftPicker->setRubberBandPen(QColor(Qt::yellow));
    _qwtLeftPicker->setRubberBand(QwtPicker::CrossRubberBand);
    _qwtLeftPicker->setTrackerPen(QColor(Qt::white));
    
    _qwtRightPicker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn, _qwtPlot->canvas());
    _qwtRightPicker->setStateMachine(new QwtPickerDragPointMachine());
    _qwtRightPicker->setRubberBandPen(QColor(Qt::yellow));
    _qwtRightPicker->setRubberBand(QwtPicker::CrossRubberBand);
    _qwtRightPicker->setTrackerPen(QColor(Qt::white));
	_qwtRightPicker->setMousePattern(QwtPicker::MouseSelect1, Qt::RightButton);

    connect(_qwtPlot, SIGNAL(legendChecked(QwtPlotItem*, bool)), this, SLOT(showItem(QwtPlotItem*, bool)));
    connect(_qwtLeftPicker, SIGNAL(selected(const QPointF&)), SLOT(leftClick(const QPointF&)));
    connect(_qwtRightPicker, SIGNAL(selected(const QPointF&)), SLOT(rightClick(const QPointF&)));

    _qwtPlot->replot(); // creating the legend items

    QwtPlotItemList items = _qwtPlot->itemList(QwtPlotItem::Rtti_PlotHistogram);
    for(int i = 0; i < items.size(); i++)
    {
        if(i == 0)
        {
            QwtLegendItem* legendItem = qobject_cast<QwtLegendItem*>(legend->find(items[i]));
            if(legendItem)
                legendItem->setChecked(true);

            items[i]->setVisible(true);
        }
        else
        {
            items[i]->setVisible(false);
        }
    }

    _qwtPlot->setAutoReplot(true);
}

void HistogramView::populate()
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
		imagein::Histogram histogram(*_image, i, *_rectangle);
		int values[histogram.getWidth()];

		for(unsigned int j = 0; j < histogram.getWidth(); ++j)
			values[j] = histogram[j];
		
		GraphicalHistogram* graphicalHisto;
		switch(i)
		{
			case 0:
				graphicalHisto = new GraphicalHistogram("Red", Qt::red);
			break;
			case 1:
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
		graphicalHisto->attach(_qwtPlot);
	}
}

void HistogramView::showItem( QwtPlotItem *item, bool on )
{
    item->setVisible( on );
}

QwtPlot* HistogramView::getHistogram()
{
	return _qwtPlot;
}

void HistogramView::leftClick(const QPointF &pos)
{
    emit(leftClickedValue((int)pos.x()));
}

void HistogramView::rightClick(const QPointF &pos)
{
    emit(rightClickedValue((int)pos.x()));
}

/*QwtText HistogramView::trackerText(const QPoint& pos) const
{
	return QwtText((int)_qwtPlot->invTransform(QwtPlot::xBottom, pos.x()));
}*/
