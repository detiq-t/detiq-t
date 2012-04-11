#include "GraphicalHistogram.h"

using namespace genericinterface;

GraphicalHistogram::GraphicalHistogram(const QString& title, const QColor& color): QwtPlotHistogram(title)
{
    setStyle(QwtPlotHistogram::Columns);
    
    QColor c = color;
    c.setAlpha(180);
    setBrush(QBrush(c));
    setPen(QPen(Qt::black));

    QwtColumnSymbol* symbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
    symbol->setFrameStyle(QwtColumnSymbol::Raised);
    symbol->setLineWidth(2);
    symbol->setPalette(QPalette(color));
    setSymbol(symbol);
}

void GraphicalHistogram::setValues(int numValues, int *values)
{
    QVector<QwtIntervalSample> samples(numValues);
    for (int i = 0; i < numValues; i++)
    {
        QwtInterval interval(double(i), i + 1.0 );
        interval.setBorderFlags(QwtInterval::ExcludeMaximum);

        samples[i] = QwtIntervalSample(values[i], interval);
    }

    setData(new QwtIntervalSeriesData(samples));
}
