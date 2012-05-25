#ifndef QTINTERFACE_WIDGET_NAVIGATIONDOCK
#define QTINTERFACE_WIDGET_NAVIGATIONDOCK

#include <QHBoxLayout>
#include <QMessageBox>
#include <QStringListModel>
#include <QMenu>
#include <QModelIndex>
#include <QAction>

#include "NavigationBar.h"

namespace genericinterface
{
class NavigationDock : public QWidget
{
    Q_OBJECT
public:
    /**
    * @brief Default constructor, layout the elements
    */
    NavigationDock();

    QStringList getSelection();

public slots:
    /**
    * @brief
    *
    * @param path
    */
    void addImage(const QString& path);
    void removeImage(const QString& path);

protected slots:
    /**
    * @brief
    *
    * @param pos
    */
    void showContextMenu(const QPoint& pos);
    void emitAction(const QModelIndex& index);
    void closeSelection();

signals:
    void actionDone();
    void removeId(const QString& path);

private:
    QStringList _data;
    QStringListModel* _model;
    NavigationBar* _view;
    QMenu* _contextMenu;

};
}

#endif
