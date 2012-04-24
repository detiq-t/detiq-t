#include <QApplication>

#include <GenericInterface.h>
#include "BasicAlgorithmService.h"

using namespace genericinterface;

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  Log::configure(true, true, 0);

  GenericInterface m;
  int serviceId = m.addService(new BasicAlgorithmService);

  m.run();

  return app.exec();
}
