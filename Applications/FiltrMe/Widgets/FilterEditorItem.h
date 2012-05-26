#ifndef WIDGET_FILTEREDITORITEM
#define WIDGET_FILTEREDITORITEM

#include <iostream>

#include <Algorithm/Filter.h>
#include <Algorithm/Filtering.h>

#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QList>
#include <QtGui/QTableWidget>
#include <QMessageBox>

class QLineEdit;

namespace filtrme
{
  class FilterEditorItem : public QWidget
  {
  Q_OBJECT
  
  public:
    FilterEditorItem();
    imagein::algorithm::Filter* validFilter();
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
  
  signals:
    void insertRow(int);
    void removeRow(int);
    void insertColumn(int);
    void removeColumn(int);
    
  private slots:
    void widthChanged(const int);
    void heightChanged(const int);
    
  private:
    void initUI();

    QTableWidget* _filter;
    int _width;
    int _height;
  };
}

#endif //WIDGET_FILTEREDITORITEM
