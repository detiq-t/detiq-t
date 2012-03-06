#include "FileService.h"

using namespace genericinterface;

void FileService::connect (GenericInterface* gi)
{
  _gi = gi;
  QObject::connect(_open, SIGNAL(triggered()), this, SLOT(chooseFile()));
  QObject::connect(this, SIGNAL(fileChosen(const QString&)), dynamic_cast<WindowService*>(gi->getService(0)), SLOT(addFile(const QString&)));
}

void FileService::display (GenericInterface* gi)
{
  _open = gi->menu("&File")->addAction("&Open");
}


void FileService::chooseFile()
{
  QString file = QFileDialog::getOpenFileName(_gi, "Open a file", QString(), "Images (*.png *.bmp *.jpg *.jpeg)");

  emit fileChosen(file);
}
