#ifndef GENERICINTERFACE_H_02022012
#define GENERICINTERFACE_H_02022012

/* Stl includes */
#include <map>

/* Qt includes */
#include <QMainWindow>
#include <QMessageBox>
#include <QMdiArea>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QString>
#include <QApplication>

namespace genericinterface
{
  class GenericInterface; /* Pre-declaration for the Service include */
  class WindowService;
  class FileService;
}

#include "InterfaceExceptions.h"
#include "Utilities/Log.h"
#include "Service.h"
#include "Services/WindowService.h"
#include "Services/FileService.h"
#include "Services/UtilityService.h"
#include "Services/AlgorithmService.h"

/**
* @brief The Generic Interface provides to the ImageIn developper a way to built easily
* a demonstration of his algorithm
*
* It is built with the philosophy of services : each functionnality of the application is
* a service running by an instance of Service interface.
*/
namespace genericinterface
{
  class GenericInterface : public QMainWindow
  {
	public:
	
	enum { WINDOW_SERVICE, FILE_SERVICE, UTILITY_SERVICE }; 

    GenericInterface(QString name = "");

    /**
    * @brief Add a new service to the generic interface and returns its id
    *
    * <p>The integer using for the identification of one service is very important : it's thanks to
    * its you will be able to connect your services with other, including the default ones. The GenericInterface
    * gives a set of minimalist services, identify by an integer :</p>
    *
    * <ul>
    *   <li> WindowService : 0 (WINDOW_SERVICE)
    *   <li> FileService : 1 (FILE_SERVICE)
    *   <li> UtilityService : 2 (UTILITY_SERVICE)
    * </ul>
    *
    * <p>
    *
    * @param s the service to add
	* @return id the identifier of the service
    */
	int addService(Service* s);
	
    /**
    * @brief Change the id service to a custom one.
    *
    * Be careful : the new service has to implemant the signals and slots of the
    * former one. If not, the connect method will throw an ServiceConnectionException
    * and your application won't be able to assume the basics tasks.
    *
    * @param id
    * @param s
    */
    void changeService(int id, Service* s) throw (BadIdException);

    /**
    * @brief Provides a direct access to the wanted service, mostly used by the Service::connect(GenericInterface*)
    * function.
    *
    * @param id its id
    *
    * @return the wanted Service
    */
    Service* getService(int id) throw (BadIdException);

    /**
    * @brief Return a pointer on the WindowService
    *
    * @return a pointer to the WindowService
    */
    WindowService* windowService();

    /**
    * @brief Return a pointer on the FileService
    *
    * @return a pointer to the FileService
    */
    FileService* fileService();

    /**
    * @brief This function has to be prefered to the Qt function void QMainWindow::show(), it connects the
    * services to each other (by simply calling the function void Service::connect(GenericInterface*) of each 
    * service added to the GenericInterface and then displays them.
    *
    * @param shw Request to QMainWindow::show(), the default value is true. 
    */
    virtual void run(bool shw = true);

    /**
    * @brief Create the Mdi Widget of the main window
    *
    * This function will throw an exception if it was already called
    *
    * @return a pointer to the created widget
    */
    virtual QMdiArea* initCentralWidget();

    /**
    * @brief Get a pointer to the QMenu labelled name, create the menu if it doesn't exist.
    *
    * @param name the label of the wanted menu
    *
    * @return the pointer
    */
    virtual QMenu* menu(QString name);

    /**
    * @brief Get a pointer to the QToolBar labelled name, create the toolBar if it doesn't exist.
    *
    * @param name the label of the wanted QToolBar
    *
    * @return the pointer
    */
    virtual QToolBar* toolBar(QString name);


  protected:
    /**
    * @brief The services the interface can uses.
    */
    std::map<int, Service*> _services;
    std::map<QString, QMenu*> _menus;
    std::map<QString, QToolBar*> _toolBars;
	
	int _nbServices;
	
	/**
    * @brief Add a new service to the generic interface
    *
    * <p>The integer using for the identification of one service is very important : it's thanks to
    * its you will be able to connect your services with other, including the default ones. The GenericInterface
    * gives a set of minimalist services, identify by an integer :</p>
    *
    * <ul>
    *   <li> WindowService : 0
    *   <li> FileService : 1
    *   <li> UtilityService : 2
    * </ul>
    *
    * <p>
    *
    * @param id the identifier of the service
    * @param s the service to add
    */
    void addService(int id, Service* s) throw (BadIdException);
	
  private:
    /**
	 * @brief Add the last elements of the interface : exit button, about qt, etc.
	 */
    void finalizeInterface();
  };
}

#endif
