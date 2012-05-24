#include "FilterChoice.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QHeaderView>

#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomImplementation>
#include <QtXml/QDomElement>
#include <QTextStream>

#include <GenericInterface.h>

using namespace filtrme;
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
  
  _filters.push_back(Filter::uniform(3));
  _filters.push_back(Filter::gaussian(1));
  _filters.push_back(Filter::prewitt(3));
  _filters.push_back(Filter::roberts());
  _filters.push_back(Filter::sobel());
  _filters.push_back(Filter::squareLaplacien());
  
  //Personal filters
  QFile file("filters.xml");
  if(file.exists())
  {
    QDomDocument doc("");
    file.open(QIODevice::ReadOnly);
	  doc.setContent(&file);
	  file.close();
    
    QDomElement root = doc.documentElement();
    QDomNode child = root.firstChild();
	  while(!child.isNull())
	  {
      QDomElement e = child.toElement();
	    // We know how to treat appearance and geometry
      blurs.push_back(e.attribute("name"));
	    
      Filter* f = new Filter(e.attribute("width").toInt(), e.attribute("height").toInt());
      QDomElement grandChild = e.firstChild().toElement();
      if(!grandChild.isNull())
      {
        // We know how to treat color
        if (grandChild.tagName() == "values")
        {
          std::string str = grandChild.text().toStdString();
          std::string word;
          std::stringstream stream(str);
          int w = 0, h = 0;
          while(getline(stream, word, ' '))
          {
            (*f)[w][h] = QString::fromStdString(word).toInt();
                          
            if(h == f->height() - 1)
            {
              h = 0;
              w++;
            }
            else
              h++;
          }
        }
      }
      std::vector<Filter*> temp;
      temp.push_back(f);
      _filters.push_back(temp);
      
      child = child.nextSibling();
	  }
  }
  
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
    default:
      filtering = new Filtering(_filters[_blurChoices->currentIndex()]);
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
    default:
      filters = _filters[_blurChoices->currentIndex()];
      _numPixels->hide();
      _labelWidth->hide();
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
