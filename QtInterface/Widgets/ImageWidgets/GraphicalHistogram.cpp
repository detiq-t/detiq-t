#include "GraphicalHistogram.h"

using namespace genericinterface;

GraphicalHistogram::GraphicalHistogram(const QString &title, const QColor &symbolColor): QwtPlotHistogram(title)
{
    setStyle(QwtPlotHistogram::Columns);
    setColor(symbolColor);
}

void GraphicalHistogram::setColor(const QColor &color)
{
    QColor c = color;
    c.setAlpha(180);
    setBrush(QBrush(c));
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
