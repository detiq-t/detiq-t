#ifndef QTINTERFACE_TESTSERVICE_H
#define QTINTERFACE_TESTSERVICE_H

#include "Service.h"

class TestService : public Service
{
public:
  void connect (GenericInterface* gi)
  {
    // After
    QObject::connect(_test, SIGNAL(triggered()), qApp, SLOT(quit()));
  }

  void display (GenericInterface* gi)
  {
    _test = gi->menu("Fichiers")->addAction("Test");
  }
private:
  QAction* _test;
};

#endif
