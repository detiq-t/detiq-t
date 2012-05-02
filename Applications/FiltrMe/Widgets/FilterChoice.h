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

namespace genericinterface
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

  private slots:
    void currentBlurChanged(int);
    void dataChanged(const QString&);
    void validate();

  private:
    void updateDisplay();
    
    QComboBox* _blurChoices;
    QComboBox* _policyChoices;
    /*
     * QComboBox* _normalizationChoices;
     */
    
    QLabel* _labelCoef;
    QLineEdit* _coef;
    QLabel* _labelWidth;
    QLineEdit* _numPixels;
    
    QTableWidget* _filterView;
    
    QVBoxLayout* _centerLayout;
  };
}

#endif //FILTERINGCHOICE_H

