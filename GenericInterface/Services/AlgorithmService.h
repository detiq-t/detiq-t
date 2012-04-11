#ifndef QTINTERFACE_ALGORITHMSERVICE_H
#define QTINTERFACE_ALGORITHMSERVICE_H

#include "../Service.h"
#include "../Widgets/ImageWidgets/StandardImageWindow.h"

#include <Algorithm.h>

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

	 void applyAlgorithm(imagein::Algorithm_t<Image>* algo);

  public slots:
    //virtual void apply();

  signals:
    void newImageWindowCreated(const QString& path, ImageWindow* widget);


  protected:
    GenericInterface* _gi;
    QToolBar* _toolBar;
  };
}

#endif
