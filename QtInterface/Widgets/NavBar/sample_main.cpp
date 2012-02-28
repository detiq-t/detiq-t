#include <QApplication>
#include <QStatusBar>
#include <QMdiArea>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <iostream>
#include <QStringList>
#include <QStringListModel>

#include "NavigationBar.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

  NavigationBar bar;
  QStringList test;

  test << "test.png" << "test.png" << "salut.png";

  QStringListModel* m = new QStringListModel(test);
  bar.setModel(m);

  bar.show();

  return app.exec();    
    
}
