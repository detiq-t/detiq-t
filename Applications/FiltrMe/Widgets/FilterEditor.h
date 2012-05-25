#ifndef WIDGET_FILTEREDITION
#define WIDGET_FILTEREDITION

#include <iostream>
#include <vector>

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
    void applyFiltering(imagein::algorithm::Filtering*);
    void cancelAction();
    
  private slots:
    void save();
    void cancel();
    void apply();
    void quit();
    void nbFiltersChanged(const int);
    
  private:
    void initUI();
    void saveXML(std::vector<imagein::algorithm::Filter*> filter);
    std::vector<imagein::algorithm::Filter*> validFilters(bool* ok);

    QVBoxLayout* _filterLayout;
    QLineEdit* _name;
    int _nbFilters;
  };
}

#endif
