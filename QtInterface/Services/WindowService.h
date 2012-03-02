#ifndef QTINTERFACE_WINDOWSERVICE_H
#define QTINTERFACE_WINDOWSERVICE_H

#include <QMessageBox>
#include <QDockWidget>

#include "../Widgets/ImageWidgets/StandardImageWindow.h"
#include "../Widgets/NavBar/NavigationDock.h"
#include "../GenericInterface.h"

typedef std::map<QString, QList<QMdiSubWindow*> > WindowsMap;

class WindowService : public QObject, public Service
{
Q_OBJECT
public:
  void connect (GenericInterface* gi);
  void display (GenericInterface* gi);

private slots:
  void addFile(const QString& path);

public slots:
  void updateDisplay();

signals:

private:
  QMdiArea* _mdi;
  NavigationDock* _nav;
  WindowsMap _windows;
};

#endif
