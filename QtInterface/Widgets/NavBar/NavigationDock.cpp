#include "NavigationDock.h"

NavigationDock::NavigationDock() : QWidget()
{
  /* Creation of the attributs */
  _model = new QStringListModel;
  _view = new NavigationBar;

  _view->setModel(_model);

  _contextMenu = new QMenu(this);

  /* Context Menu */
  QAction* test = _contextMenu->addAction("test");
  setContextMenuPolicy(Qt::CustomContextMenu);

  QObject::connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

  /* layout */
  QHBoxLayout* layout = new QHBoxLayout;

  setLayout(layout);
  layout->addWidget(_view);

  setFixedWidth(110);
}

void NavigationDock::addImage(const QString& path)
{
  _data << path;
  _model->setStringList(_data);
}

void NavigationDock::showContextMenu(const QPoint& pos)
{
  _contextMenu->popup(mapToGlobal(pos));
}
