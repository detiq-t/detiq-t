#include "NavigationDock.h"

using namespace genericinterface;

NavigationDock::NavigationDock() : QWidget()
{
    /* Creation of the attributs */
    _model = new QStringListModel;
    _view = new NavigationBar;

    _view->setModel(_model);
    _view->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QObject::connect(_view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(emitAction(const QModelIndex&)));

    _contextMenu = new QMenu(this);

    /* Context Menu */
    _contextMenu->addAction("Close all image from the selection", this, SLOT(closeSelection()));

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

void NavigationDock::removeImage(const QString& path)
{
    _data.removeAll(path);
    _model->setStringList(_data);
}

void NavigationDock::showContextMenu(const QPoint& pos)
{
    _contextMenu->popup(mapToGlobal(pos));
}

void NavigationDock::emitAction(const QModelIndex& index)
{
    emit actionDone();
}

void NavigationDock::closeSelection()
{
    int answer = QMessageBox::question(this, "Attention", "You're going to close all the relative windows, are you sure you want to continue?", QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes)
    {
        QStringList selection = this->getSelection();
        for (int i=0; i<selection.size(); i++)
        {
            emit removeId(selection[i]);
        }
    }
}
