#include "FileService.h"
#include "WindowService.h"

#include <UnknownFormatException.h>

#include <QMessageBox>
#include <QDebug>

using namespace genericinterface;

void FileService::connect (GenericInterface* gi)
{
	_gi = gi;
	QObject::connect(_open, SIGNAL(triggered()), this, SLOT(chooseFile()));
	//QObject::connect(_save, SIGNAL(triggered()), this, SLOT(save()));
	QObject::connect(_saveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
  
	QObject::connect(this, SIGNAL(fileChosen(const QString&)), dynamic_cast<WindowService*>(gi->getService(GenericInterface::WINDOW_SERVICE)), SLOT(addFile(const QString&)));
	
    //connexion des changements d'images
	WindowService* ws = dynamic_cast<WindowService*>(gi->getService(GenericInterface::WINDOW_SERVICE));
	QObject::connect(ws, SIGNAL(subWindowActivated(QMdiSubWindow*)), this, SLOT(checkActionsValid(QMdiSubWindow*)));
}

void FileService::display (GenericInterface* gi)
{
    _open = gi->menu("&File")->addAction("&Open");
    //_save = gi->menu("&File")->addAction("&Save");
    _saveAs = gi->menu("&File")->addAction("Save &As");
    
    //_save->setEnabled(false);
    _saveAs->setEnabled(false);
}

void FileService::save(const QString& path, const QString& ext)
{
	if(path == "") {
		this->saveAs();
	}
	else {
        try {
            WindowService* ws = dynamic_cast<WindowService*>(_gi->getService(GenericInterface::WINDOW_SERVICE));
            if(ws != NULL) {
                StandardImageWindow* imw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
                if(imw != NULL) {
					try {
						imw->getImage()->save(path.toStdString()); 
					}
					catch(const UnknownFormatException& e) {
						if(ext == "")
							throw e;
						
						imw->getImage()->save((path+ext).toStdString()); 
					}
                }
                else {
                    QMessageBox::critical(_gi, "Bad object type", "Only images can be saved at the moment.");
                }
            }
        }
        catch(const char* s) {
                QMessageBox::information(_gi, "plop", s);
        }
	}
}

void FileService::saveAs()
{
    QString selectedFilter;
	QString path = QFileDialog::getSaveFileName(_gi, "Save a file", QString(), "Png image (*.png);;Bmp image (*.bmp);; Jpeg image(*.jpg)", &selectedFilter);

	QString ext = selectedFilter.right(5).left(4);
	if(!path.contains('.')) path += ext;

	if(path != "") {
		this->save(path, ext);
	}
}

void FileService::chooseFile()
{
  QString file = QFileDialog::getOpenFileName(_gi, "Open a file", QString(), "Images (*.png *.bmp *.jpg *.jpeg)");

  if(file != "")
    emit fileChosen(file);
}

void FileService::checkActionsValid(QMdiSubWindow* activeWindow)
{
	StandardImageWindow* window = (activeWindow) ? dynamic_cast<StandardImageWindow*>(activeWindow->widget()) : NULL;
	if(window) {
		//_save->setEnabled(true);
		_saveAs->setEnabled(true);
	}
	else {
		//_save->setEnabled(false);
		_saveAs->setEnabled(false);
	}
}
