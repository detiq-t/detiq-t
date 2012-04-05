#include <QApplication>

#include <GenericInterface.h>
#include "BasicAlgorithmService.h"

using namespace genericinterface;

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  Log::configure(true, false, 0);

  GenericInterface m;
  m.addService(2, new BasicAlgorithmService);

  m.run();

  return app.exec ();
}
