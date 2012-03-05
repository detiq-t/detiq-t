#include "NavigationDock.h"

using namespace genericinterface;

NavigationDock::NavigationDock() : QWidget()
{
  /* Creation of the attributs */
  _model = new QStringListModel;
  _view = new NavigationBar;

  _view->setModel(_model);
  _view->setSelectionMode(QAbstractItemView::ExtendedSelection);

  QObject::connect(_view, SIGNAL(clicked (const QModelIndex&)), this, SLOT(emitAction(const QModelIndex&)));

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

QStringList NavigationDock::getSelection()
{
  QItemSelectionModel *selection = _view->selectionModel();
  QModelIndexList listSelect = selection->selectedIndexes();

  QStringList res;

  for(int i = 0; i < listSelect.size(); i++)
  {
    res << _model->data(listSelect[i], Qt::DisplayRole).toString();
  }

  return res;
}

void NavigationDock::addImage(const QString& path)
{
  _data << path;
  _model->setStringList(_data);
}

void NavigationDock::emitAction(const QModelIndex& index)
{
  emit actionDone();
}

void NavigationDock::showContextMenu(const QPoint& pos)
{
  _contextMenu->popup(mapToGlobal(pos));
}
