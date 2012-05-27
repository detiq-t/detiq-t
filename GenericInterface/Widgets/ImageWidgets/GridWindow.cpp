#include <QVBoxLayout>

#include "GridWindow.h"
#include "GridView.h"
#include "ZoomViewer.h"
#include "../ImageWidgets/StandardImageWindow.h"

using namespace imagein;
using namespace genericinterface;

GridWindow::GridWindow(QString & path, ImageWindow* source) : ImageWindow(path, source, 0)
{
  QVBoxLayout* box = new QVBoxLayout;

  Image* im = new Image(path.toStdString());

  _view = new GridView(im, path, 0, 0);

  box->addWidget(_view);
  
  this->setWindowTitle(ImageWindow::getTitleFromPath(path) + QString::fromStdString(" - Pixels Grid"));

  setLayout(box);
}
