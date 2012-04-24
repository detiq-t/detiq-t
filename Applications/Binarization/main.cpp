#include <QApplication>

#include <GenericInterface.h>
#include "Services/BinarizationService.h"
#include "Services/BasicTools.h"

#include <iostream>

using namespace genericinterface;
using namespace std;

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  Log::configure(true, false, 0);

  GenericInterface m;

  int basicToolsID = m.addService(new BasicTools);
  int binarizationServiceID = m.addService(new BinarizationService);

  m.run();

  return app.exec();
}
