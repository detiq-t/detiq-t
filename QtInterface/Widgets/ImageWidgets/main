#include <QApplication>
#include <QStatusBar>
#include <QMdiArea>
#include <QLabel>
#include <QImage>
#include <iostream>

#include "StandardImageWindow.h"
#include "../../ImageIn/Image.h"

using namespace imagein;
using namespace genericinterface;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	
	QMdiArea* mainWindow = new QMdiArea();
	
    Image* image = new Image("../../ImageIn/samples/gnu.png");
	StandardImageWindow* w = new StandardImageWindow(mainWindow, image);
	mainWindow->addSubWindow(w);
	w->show();
	mainWindow->show();

    return app.exec();    
    
}
