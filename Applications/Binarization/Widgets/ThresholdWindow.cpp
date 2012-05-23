#include "ThresholdWindow.h"

#include <Image.h>

using namespace genericinterface;
using namespace imagein;

ThresholdWindow::ThresholdWindow(StandardImageWindow* imw, int threshold)
{
  QVBoxLayout* layout = new QVBoxLayout();
  this->setLayout(layout);
  
  // Top panel
  Rectangle* rect = new Rectangle(*(imw->getSelection()));
  _histo = new HistogramWindow(imw->getPath(), imw->getImage(), rect, imw);
  layout->addWidget(_histo);

  // Bottom panel
  QString text = "Threshold computed by Otsu's algorithm :" + QString::number(threshold);
  _labelThreshold = new QLabel(text, this);
  layout->addWidget(_labelThreshold);
}
