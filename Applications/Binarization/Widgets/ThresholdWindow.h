#ifndef THRESHOLDWINDOW_H 
#define THRESHOLDWINDOW_H

#include <Widgets/ImageWidgets/StandardImageWindow.h>
#include <Widgets/ImageWidgets/HistogramWindow.h>

#include <QWidget>
#include <QLabel>
#include <QString>

namespace genericinterface
{
  class ThresholdWindow : public QWidget
  {
  public:
    ThresholdWindow(StandardImageWindow* imw, int threshold);

  protected:

  private:
    HistogramWindow* _histo;
    QLabel* _labelThreshold;
  };
}

#endif
