#include "BitPlaneWindow.h"

using namespace bitplane;
using namespace imagein;
using namespace algorithm;
using namespace genericinterface;

BitPlaneWindow::BitPlaneWindow(const QString & path, GenericInterface* gi, Image* image) : StandardImageWindow(path,gi,image)
{
  _workImg = _image;
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
  BitPlane<Image> bp = BitPlane<Image>(_bitplanechoice->getMask());
  _image = bp(_workImg);
  // TODO changer l'image de imageView, par exemple un truc du genre : _imageView->setNewImage(_image);
  std::string newTitle = "Image with bit plane ";
  newTitle+=(_bitplanechoice->getStrMask()).toStdString();
  newTitle+=" - ";
  newTitle+=_path.toStdString();
  this->setWindowTitle(newTitle.c_str());
}
