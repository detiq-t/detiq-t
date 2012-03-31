#ifndef QTINTERFACE_ALGORITHMSERVICE_H
#define QTINTERFACE_ALGORITHMSERVICE_H

#include "../Service.h"
//#include "../GenericInterface.h"

#include <QToolBar>

namespace genericinterface
{
  class AlgorithmService : public QObject, public Service
  {
  Q_OBJECT
  public:
    AlgorithmService();

    virtual void display(GenericInterface* gi);
    virtual void connect(GenericInterface* gi);

  public slots:
    //virtual void apply();

  protected:
    GenericInterface* _gi;
    QToolBar* _toolBar;
  };
}

#endif
