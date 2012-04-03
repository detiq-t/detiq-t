#include <QApplication>
#include <GenericInterface.h>

using namespace genericinterface;

int main (int argc, char** argv)
{
  QApplication app (argc, argv);

  Log::configure (true, false, 0);

  GenericInterface m;

  m.run ();

  return app.exec ();
}
