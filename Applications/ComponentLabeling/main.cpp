#include <QApplication>

#include <GenericInterface.h>
#include "ComponentLabelingService.h"

using namespace genericinterface;

int main (int argc, char** argv)
{
  QApplication app (argc, argv);

  Log::configure (true, false, 0);

  GenericInterface m("Component Labelling");
  m.addService(new ComponentLabelingService);

  m.run();

  return app.exec ();
}
