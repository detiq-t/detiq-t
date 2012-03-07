#include <QApplication>

#include "ImageViewer.h"

using namespace genericinterface;

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QWidget t;
  
  ImageViewer im("salut.png", 200, 500);

  im.show();

  t.show();

  return app.exec();
}
