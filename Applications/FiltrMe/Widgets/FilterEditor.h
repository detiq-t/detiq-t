#ifndef WIDGET_FILTEREDITION
#define WIDGET_FILTEREDITION

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
  class FilterEditor : public QWidget
  {
  Q_OBJECT
  
  public:
    FilterEditor();

  
  signals:
    void insertRow(int);
    void removeRow(int);
    void insertColumn(int);
    void removeColumn(int);
    void applyFiltering(imagein::algorithm::Filtering*);
    void cancelAction();
    
  private slots:
    void save();
    void cancel();
    void apply();
    void widthChanged(const int);
    void heightChanged(const int);
    
  private:
    void initUI();
    void saveXML(imagein::algorithm::Filter* filter);
    imagein::algorithm::Filter* validFilter();

    QTableWidget* _filter;
    QLineEdit* _name;
    int _width;
    int _height;
  };
}

#endif
