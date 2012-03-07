#ifndef QTINTERFACE_WINDOWSERVICE_H
#define QTINTERFACE_WINDOWSERVICE_H

#include <QMessageBox>
#include <QDockWidget>

#include "../Widgets/ImageWidgets/ImageWindow.h"
#include "../Widgets/ImageWidgets/StandardImageWindow.h"
#include "../Widgets/NavBar/NavigationDock.h"
#include "../GenericInterface.h"

typedef std::map<QString, QList<QMdiSubWindow*> > WindowsMap;

namespace genericinterface
{
  class WindowService : public QObject, public Service
  {
  Q_OBJECT
  public:
    void connect (GenericInterface* gi);
    void display (GenericInterface* gi);
    void addWidget(const QString & path, ImageWindow* widget);

  private slots:
    void addFile(const QString& path);
	 void removeSubWindow(const QString& path, QMdiSubWindow* sw);

  public slots:
    void updateDisplay();

  signals:

  private:
    GenericInterface* _gi;
    QMdiArea* _mdi;
    NavigationDock* _nav;
    WindowsMap _windows;
  };


  //TODO Détruire le Controller une fois l'image retirée de la WindowsMap ! 
  class SubWindowController : public QObject
  {
  Q_OBJECT
  public:
    SubWindowController(const QString& path, QMdiSubWindow* sw);
  
  public slots:
  	 void closeSubWindow();

  signals:
    void removeFromWindowsMap(const QString& path, QMdiSubWindow* sw);

  private:
    QString _path;
	 QMdiSubWindow* _sw;
  };
}

#endif
