#include <QApplication>

#include <GenericInterface.h>
#include "Services/MorphoMatService.h"

#include <iostream>

using namespace genericinterface;
using namespace std;

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  Log::configure(true, false, 0);

  GenericInterface m("MorphoMat");

  m.addService(new MorphoMatService);

  m.run();

  return app.exec();
}
