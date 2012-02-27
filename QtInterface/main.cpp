#include <QApplication>
#include "GenericInterface.h"
#include "Log.h"
#include "TestService.h"

int main (int argc, char** argv)
{
  QApplication app (argc, argv);
  TestService* t = new TestService;

  Log::configure (true, false, 0);

  GenericInterface m;
  m.addService(0, t);

  m.run ();

  return app.exec ();
}
