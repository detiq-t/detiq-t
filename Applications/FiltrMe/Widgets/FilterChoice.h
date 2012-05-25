#ifndef FILTERINGCHOICE_H
#define FILTERINGCHOICE_H

#include <Services/AlgorithmService.h>

#include <Algorithm/Filter.h>
#include <Algorithm/Filtering.h>

#include <vector>
#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QSpinBox>

namespace filtrme
{
  /*!
   * \brief Implementation of AlgorithmService for Filtering application
	*
	* It allows to apply filter on image
	*/
  class FilterChoice : public QWidget
  {
  Q_OBJECT
  
  public:
    FilterChoice();
  
  signals:
    void choiceValidate(imagein::algorithm::Filtering* filtering);
    void cancelAction();
  
  private slots:
    void currentBlurChanged(int);
    void dataChanged(const QString&);
    void validate();
    void cancel();
    void deleteFilter();

  private:
    void initUI();
    void updateDisplay();
    
    std::vector< std::vector< imagein::algorithm::Filter* > > _filters;
    
    QComboBox* _blurChoices;
    QComboBox* _policyChoices;
    
    QLabel* _labelNumber;
    QSpinBox* _number;
    
    QTableWidget* _filterView;
    QPushButton* _deleteButton;
  };
}

#endif //FILTERINGCHOICE_H

