#ifndef QTINTERFACE_IDENTITYALGORITHMSERVICE_H
#define QTINTERFACE_IDENTITYALGORITHMSERVICE_H

#include "AlgorithmService.h"
#include "../Widgets/ImageWidgets/StandardImageWindow.h"

//#include "../GenericInterface.h"

namespace genericinterface
{
  class IdentityAlgorithmService : public AlgorithmService
  {
  Q_OBJECT
  public:
    void connect(GenericInterface* gi);
    void display(GenericInterface* gi);

  public slots:
    void apply();

  signals:
    void newImageWindowCreated(const QString& path, ImageWindow* widget);

  private:
    QAction* _apply;
  };
}

#endif
