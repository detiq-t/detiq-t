#include "RowView.h"

using namespace genericinterface;
using namespace imagein;

RowView::RowView(Image* image, Rectangle* rect): AlternativeImageView(image), _rectangle(rect)
{
	_qwtPlot = new QwtPlot();
	init();
}

void RowView::init()
{
    this->setMouseTracking(true); //Switch on mouse tracking (no need to press button)

    _qwtPlot->setTitle("Profile Histogram");
    
    _qwtPlot->setCanvasBackground(QColor(Qt::gray));
    _qwtPlot->plotLayout()->setAlignCanvasToScales(true);

    _qwtPlot->setAxisTitle(QwtPlot::yLeft, "Number of specimen");
    _qwtPlot->setAxisTitle(QwtPlot::xBottom, "Pixel value");

	QwtLegend* legend = new QwtLegend();
    legend->setItemMode(QwtLegend::CheckableItem);
    _qwtPlot->insertLegend(legend, QwtPlot::RightLegend);

    populate();
    
    _qwtPlot->canvas()->setMouseTracking(true);
    
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

void RowView::populate()
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

void RowView::showItem( QwtPlotItem *item, bool on )
{
    item->setVisible( on );
}

imagein::Histogram* RowView::getHistogram(int channel) const
{
	return new imagein::Histogram(*_image, channel, *_rectangle);
}

QwtPlot* RowView::getGraphicalHistogram() const
{
	return _qwtPlot;
}

void RowView::leftClick(const QPointF& pos)
{
    emit(leftClickedValue((int)pos.x()));
}

void RowView::rightClick(const QPointF& pos)
{
    emit(rightClickedValue((int)pos.x()));
}

void RowView::move(const QPointF& pos) const
{
	emit(hoveredValue((int)pos.x()));
}
