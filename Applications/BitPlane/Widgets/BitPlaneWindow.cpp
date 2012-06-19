/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    unsigned int c = image->getNbChannels();
    unsigned int i,j,k;
    for(i=0;i<w;i++) {
      for(j=0;j<h;j++) {
        for(k=0;k<c;k++) {
          image->setPixel(i,j,k,image->getPixel(i,j,k)*255/m);
        }
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
