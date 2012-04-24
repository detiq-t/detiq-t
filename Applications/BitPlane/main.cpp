#include <QApplication>
#include <GenericInterface.h>
#include "Services/BitPlaneService.h"

using namespace genericinterface;

int main (int argc, char** argv)
{
  QApplication app (argc, argv);

  Log::configure (true, false, 0);

  GenericInterface m;
  int serviceId = m.addService(new BitPlaneService);

  m.run ();

  return app.exec ();
}
