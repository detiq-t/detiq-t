#ifndef QTINTERFACE_WINDOWSERVICE_H
#define QTINTERFACE_WINDOWSERVICE_H

#include <QDockWidget>
#include <QMdiSubWindow>

#include "../Widgets/ImageWidgets/StandardImageWindow.h"
#include "../Widgets/ImageWidgets/ImageWindow.h"
#include "../Widgets/NavBar/NavigationDock.h"
#include "../GenericInterface.h"

typedef std::map<QString, QList<QMdiSubWindow*> > WindowsMap;

namespace genericinterface
{
  class WindowService : public QObject, public Service
  {
  Q_OBJECT
  public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);
    ImageWindow* getCurrentImageWindow(); 

  private slots:
    void removeSubWindow(const QString& path, QMdiSubWindow* sw);
    void removePath(const QString& path);

  public slots:
    void addFile(const QString& path);
    void addWidget(const QString& path, QWidget* widget);
    void updateDisplay();
    void removeRootImage(const QString& path);

  signals:
    void subWindowActivated(QMdiSubWindow*);
	
  private:
    GenericInterface* _gi;
    QMdiArea* _mdi;
    NavigationDock* _nav;
    WindowsMap _windows;
  };


  class SubWindowController : public QObject
  {
  Q_OBJECT
  public:
    SubWindowController(const QString& path, QMdiSubWindow* sw, bool isRootImage);
  
  public slots:
  	void closeSubWindow();

  signals:
    void removeFromWindowsMap(const QString& path, QMdiSubWindow* sw);
    void removeFromWindowsMapAllPath(const QString& path);

  private:
    QString _path;
    QMdiSubWindow* _sw;
    bool _isRootImage;
  };
}

#endif
