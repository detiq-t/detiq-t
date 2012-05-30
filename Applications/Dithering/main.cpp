#include <QApplication>

#include <GenericInterface.h>
#include "DitheringService.h"

using namespace genericinterface;

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  Log::configure(true, true, 0);

  GenericInterface m("Dithering");
  m.addService(new DitheringService);

  m.run();

  return app.exec();
}
