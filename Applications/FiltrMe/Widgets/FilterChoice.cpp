#include "FilterChoice.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QHeaderView>

#include <GenericInterface.h>

using namespace genericinterface;
using namespace imagein;
using namespace algorithm;

FilterChoice::FilterChoice()
{
  QHBoxLayout* princLayout = new QHBoxLayout();
  this->setLayout(princLayout);
  
  /*
   * Left Panel
   */
  QWidget* leftPanel = new QWidget();
  QVBoxLayout* leftLayout = new QVBoxLayout();
  leftPanel->setLayout(leftLayout);
  
  QLabel* labelBlurChoice = new QLabel("Blur:");
  leftLayout->addWidget(labelBlurChoice);
  QStringList blurs = QStringList();
  blurs.push_back("Uniform");
  blurs.push_back("Gaussian");
  blurs.push_back("Prewitt");
  blurs.push_back("Roberts");
  blurs.push_back("Sobel");
  blurs.push_back("SquareLaplacien");
  _blurChoices = new QComboBox();
  _blurChoices->addItems(blurs);
  QObject::connect(_blurChoices, SIGNAL(currentIndexChanged(int)), this, SLOT(currentBlurChanged(int)));
  leftLayout->addWidget(_blurChoices);
  
  QLabel* labelPolicyChoice = new QLabel("Policy:");
  leftLayout->addWidget(labelPolicyChoice);
  QStringList policies = QStringList();
  policies.push_back("Black");
  policies.push_back("Mirror");
  policies.push_back("Nearest");
  policies.push_back("Spherical");
  _policyChoices = new QComboBox();
  _policyChoices->addItems(policies);
  leftLayout->addWidget(_policyChoices);
  
  princLayout->addWidget(leftPanel);
  
  /*
   * Center Panel
   */
  QWidget* centerPanel = new QWidget();
  _centerLayout = new QVBoxLayout();
  centerPanel->setLayout(_centerLayout);
  
  _labelCoef = new QLabel("Coefficient:");
  _centerLayout->addWidget(_labelCoef);
  _coef = new QLineEdit("1");
  _centerLayout->addWidget(_coef);
  _coef->hide();
  _labelCoef->hide();
  QObject::connect(_coef, SIGNAL(textChanged(const QString&)), this, SLOT(dataChanged(const QString&)));
  
  _labelWidth = new QLabel("Number of pixels:");
  _centerLayout->addWidget(_labelWidth);
  _numPixels = new QLineEdit("3");
  _centerLayout->addWidget(_numPixels);
  QObject::connect(_numPixels, SIGNAL(textChanged(const QString&)), this, SLOT(dataChanged(const QString&)));
  
  princLayout->addWidget(centerPanel);
  
  /*
   * Right Panel
   */
  QWidget* rightPanel = new QWidget();
  QVBoxLayout* rightLayout = new QVBoxLayout();
  rightPanel->setLayout(rightLayout);
  
  _filterView = new QTableWidget(3, 3);
  _filterView->setDragEnabled(false);
  _filterView->setCornerButtonEnabled(false);
  
  _filterView->verticalHeader()->hide();
  _filterView->horizontalHeader()->hide();
  
  int numPixels = _numPixels->text().toInt();
  for(int i = 0; i < numPixels; i++)
  {
    _filterView->setColumnWidth(i, _filterView->rowHeight(0));
    for(int j = 0; j < numPixels; j++)
    {
      QTableWidgetItem* item = new QTableWidgetItem(_coef->text());
      item->setTextAlignment(Qt::AlignHCenter);
      item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
      _filterView->setItem(i, j, item);
    }
  }
  rightLayout->addWidget(_filterView); 
  
  QPushButton* validation = new QPushButton("Validate");
  QObject::connect(validation, SIGNAL(clicked()), this, SLOT(validate()));
  rightLayout->addWidget(validation); 
  
  princLayout->addWidget(rightPanel);
  
}

void FilterChoice::currentBlurChanged(int)
{
  updateDisplay();
}

void FilterChoice::dataChanged(const QString&)
{
  if(_coef->text() != "" && _numPixels->text() != "")
    updateDisplay();
}

void FilterChoice::validate()
{
  Filtering* filtering;
  int coef = _coef->text().toInt();
  int numPixels = _numPixels->text().toInt();
  switch(_blurChoices->currentIndex())
  {
    case 0:
      filtering = new Filtering(Filtering::uniformBlur(numPixels));
      break;
    case 1:
      filtering = new Filtering(Filtering::gaussianBlur(coef));
      break;
    case 2:
      filtering = new Filtering(Filtering::prewitt(numPixels));
      break;
    case 3:
      filtering = new Filtering(Filtering::roberts());
      break;
    case 4:
      filtering = new Filtering(Filtering::sobel());
      break;
    case 5:
      filtering = new Filtering(Filtering::squareLaplacien());
      break;
    default:
      filtering = new Filtering(Filtering::uniformBlur(numPixels));
  }
  
  switch(_policyChoices->currentIndex())
  {
    case 0:
      filtering->setPolicy(Filtering::blackPolicy);
      break;
    case 1:
      filtering->setPolicy(Filtering::mirrorPolicy);
      break;
    case 2:
      filtering->setPolicy(Filtering::nearestPolicy);
      break;
    case 3:
      filtering->setPolicy(Filtering::sphericalPolicy);
      break;
    default:
      filtering->setPolicy(Filtering::blackPolicy);
  }
  
  emit choiceValidate(filtering);
}

void FilterChoice::updateDisplay()
{
  std::vector<Filter*> filters;
  int coef = _coef->text().toInt();
  int numPixels = _numPixels->text().toInt();
  switch(_blurChoices->currentIndex())
  {
    case 0:
      filters = Filter::uniform(numPixels);
      _numPixels->show();
      _labelWidth->show();
      _coef->hide();
      _labelCoef->hide();
      break;
    case 1:
      filters = Filter::gaussian(coef);
      _numPixels->hide();
      _labelWidth->hide();
      _coef->show();
      _labelCoef->show();
      break;
    case 2:
      filters = Filter::prewitt(numPixels);
      _numPixels->show();
      _labelWidth->show();
      _coef->hide();
      _labelCoef->hide();
      break;
    case 3:
      filters = Filter::roberts();
      _numPixels->hide();
      _labelWidth->hide();
      _coef->hide();
      _labelCoef->hide();
      break;
    case 4:
      filters = Filter::sobel();
      _numPixels->hide();
      _labelWidth->hide();
      _coef->hide();
      _labelCoef->hide();
      break;
    case 5:
      filters = Filter::squareLaplacien();
      _numPixels->hide();
      _labelWidth->hide();
      _coef->hide();
      _labelCoef->hide();
      break;
    default:
      filters = Filter::uniform(numPixels);
      _numPixels->show();
      _labelWidth->show();
      _coef->hide();
      _labelCoef->hide();
  }
  
  int height(0), width(0);
  
  for(unsigned int i = 0; i < filters.size(); i++)
  {
    if(height > 0)
      height++;
    height += filters[i]->height();
    if(filters[i]->width() > width)
      width = filters[i]->width();
  }
  _filterView->setRowCount(height);
  _filterView->setColumnCount(width);
  for(int i = 0; i < height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      QTableWidgetItem* item = new QTableWidgetItem("");
      item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
      _filterView->setItem(i, j, item);
    }
  }
  
  height = 0;
  for(unsigned int i = 0; i < filters.size(); i++)
  {
    for(int j = height; j < filters[i]->width() + height; j++)
    {
      for(int k = 0; k < filters[i]->height(); k++)
      {
        int value = (*filters[i])[j - height][k];
        QTableWidgetItem* item = new QTableWidgetItem(QString::number(value));
        item->setTextAlignment(Qt::AlignHCenter);
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        _filterView->setItem(j, k, item);
        _filterView->setColumnWidth(k, _filterView->rowHeight(0));
      }
    }
    
    height += filters[i]->width();
    for(int k = 0; k < filters[i]->height(); k++)
    {
      QTableWidgetItem* item = new QTableWidgetItem("");
      item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
      _filterView->setItem(height, k, item);
    }
    
    height++;
  }
}
