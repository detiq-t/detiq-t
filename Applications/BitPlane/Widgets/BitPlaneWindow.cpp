#include "BitPlaneWindow.h"

using namespace bitplane;
using namespace imagein;
using namespace algorithm;
using namespace genericinterface;

BitPlaneWindow::BitPlaneWindow(const QString & path, GenericInterface* gi, Image* image) : StandardImageWindow(path,gi,image)
{
  _workImg = new Image(*_image);
  this->setWindowTitle("Image with bit plane [1 1 1 1 1 1 1 1] - " + path);
  _bitplanechoice = new BitPlaneChoice(this);
  QObject::connect(_bitplanechoice, SIGNAL(newMaskAllocated()), this, SLOT(changeMask()));
  QVBoxLayout* layout = (QVBoxLayout*)this->layout();
  layout->removeWidget(_imageView->getGraphicsView());
  layout->removeWidget(_statusBar);
  layout->addWidget(_bitplanechoice);
  layout->addWidget(_imageView->getGraphicsView());
  layout->addWidget(_statusBar);
}

void BitPlaneWindow::changeMask()
{
  uint8_t m = _bitplanechoice->getMask();
  BitPlane<Image> bp = BitPlane<Image>(m);
  Image* image = bp(_workImg);
  if(m!=0) {
    unsigned int w = image->getWidth();
    unsigned int h = image->getHeight();
    unsigned int i,j;
    for(i=0;i<w;i++) {
      for(j=0;j<h;j++) {
        image->setPixel(i,j,0,image->getPixel(i,j,0)*255/m);
        image->setPixel(i,j,1,image->getPixel(i,j,1)*255/m);
        image->setPixel(i,j,2,image->getPixel(i,j,2)*255/m);
      }
    }
  }
  setImage(image);
  std::string newTitle = "Image with bit plane ";
  newTitle+=(_bitplanechoice->getStrMask()).toStdString();
  newTitle+=" - ";
  newTitle+=_path.toStdString();
  this->setWindowTitle(newTitle.c_str());
}
