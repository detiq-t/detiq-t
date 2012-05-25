#include "FilterChoice.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTableView>

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
  initUI();
}

void FilterChoice::initUI()
{
  QDialogButtonBox *buttonBox;
  QLabel *label;
  QLabel *label_2;

  this->setWindowTitle("FilterChoice");
  this->setMinimumSize(623, 374);
  buttonBox = new QDialogButtonBox(this);
  buttonBox->setGeometry(QRect(260, 310, 341, 32));
  buttonBox->setOrientation(Qt::Horizontal);
  buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
  QPushButton* applyButton = buttonBox->addButton(QString::fromStdString("Apply"), QDialogButtonBox::ApplyRole);
  _deleteButton = buttonBox->addButton(QString::fromStdString("Delete"), QDialogButtonBox::ActionRole);
  _deleteButton->setGeometry(QRect(310, 310, 98, 27));
  _deleteButton->setEnabled(false);
  
  QObject::connect(applyButton, SIGNAL(clicked()), this, SLOT(validate()));
  QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));
  QObject::connect(_deleteButton, SIGNAL(clicked()), this, SLOT(deleteFilter()));
  
  label = new QLabel(this);
  label->setText("Blur:");
  label->setGeometry(QRect(70, 80, 66, 17));
  label_2 = new QLabel(this);
  label_2->setText("Policy");
  label_2->setGeometry(QRect(60, 150, 66, 17));
  _labelNumber = new QLabel(this);
  _labelNumber->setText("Number of pixels:");
  _labelNumber->setGeometry(QRect(30, 220, 241, 17));
  _number = new QSpinBox(this);
  _number->setValue(3);
  _number->setMinimum(1);
  _number->setGeometry(QRect(170, 210, 60, 27));
  
  QObject::connect(_number, SIGNAL(valueChanged(const QString&)), this, SLOT(dataChanged(const QString&)));
  
  /* INIT FILTER */
  _filterView = new QTableWidget(3, 3, this);
  _filterView->setGeometry(QRect(300, 20, 311, 281));
  _filterView->verticalHeader()->hide();
  _filterView->horizontalHeader()->hide();
  _filterView->setDragEnabled(false);
  _filterView->setCornerButtonEnabled(false);
  
  int numPixels = _number->value();
  for(int i = 0; i < numPixels; i++)
  {
    _filterView->setColumnWidth(i, _filterView->rowHeight(0));
    for(int j = 0; j < numPixels; j++)
    {
      QTableWidgetItem* item = new QTableWidgetItem("1");
      item->setTextAlignment(Qt::AlignHCenter);
      item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
      _filterView->setItem(i, j, item);
    }
  }
  
  /* BLUR CHOICE */
  _blurChoices = new QComboBox(this);
  _blurChoices->setGeometry(QRect(140, 80, 141, 27));
  
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
      
      int nbFilters = e.attribute("nbFilters").toInt();
      
      std::vector<Filter*> temp;
      QDomNode grandChild = e.firstChild();
      for(int i = 0; i < nbFilters && !grandChild.isNull(); i++)
      {
        QDomElement grandChildElement = grandChild.toElement();
        if(!grandChildElement.isNull())
        {
          Filter* f = new Filter(grandChildElement.attribute("width").toInt(), grandChildElement.attribute("height").toInt());
          // We know how to treat color
          if (grandChildElement.tagName() == "values")
          {
            std::string str = grandChildElement.text().toStdString();
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
          temp.push_back(f);
        }
        grandChild = grandChild.nextSibling();
      }
      _filters.push_back(temp);
      
      child = child.nextSibling();
	  }
  }
  _blurChoices->addItems(blurs);
  QObject::connect(_blurChoices, SIGNAL(currentIndexChanged(int)), this, SLOT(currentBlurChanged(int)));
  
  /* POLICIES CHOICE */
  _policyChoices = new QComboBox(this);
  _policyChoices->setGeometry(QRect(140, 150, 141, 27));
  
  QStringList policies = QStringList();
  policies.push_back("Black");
  policies.push_back("Mirror");
  policies.push_back("Nearest");
  policies.push_back("Spherical");
  _policyChoices->addItems(policies);
}

void FilterChoice::currentBlurChanged(int)
{
  updateDisplay();
}

void FilterChoice::dataChanged(const QString&)
{
  updateDisplay();
}

void FilterChoice::validate()
{
  Filtering* filtering;
  int num = _number->value();
  
  switch(_blurChoices->currentIndex())
  {
    case 0:
      filtering = new Filtering(Filtering::uniformBlur(num));
      break;
    case 1:
      filtering = new Filtering(Filtering::gaussianBlur(num));
      break;
    case 2:
      filtering = new Filtering(Filtering::prewitt(num));
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

void FilterChoice::cancel()
{
  emit(cancelAction());
}

void FilterChoice::deleteFilter()
{
  QMessageBox msgBox(QMessageBox::Warning, "Warning!", "This filter will be lost for ever!");
  msgBox.setInformativeText("Do you want to continue?");
  msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
  msgBox.setDefaultButton(QMessageBox::No);
  
  if(msgBox.exec() == QMessageBox::Yes)
  {
    QString name = _blurChoices->itemText(_blurChoices->currentIndex());
    _blurChoices->setCurrentIndex(_blurChoices->currentIndex() - 1);
    _blurChoices->removeItem(_blurChoices->currentIndex() + 1);
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
        if (e.attribute("name") == name)
        {
          doc.documentElement().removeChild(child);
          break;
        }
        child = child.nextSibling();
      }
      
      if(file.open(QFile::WriteOnly))
      {
        QTextStream out(&file);
        out << doc.toString();
        file.close();
      }
    }
  }
}

void FilterChoice::updateDisplay()
{
  std::vector<Filter*> filters;
  int num = _number->value();
  switch(_blurChoices->currentIndex())
  {
    case 0:
      filters = Filter::uniform(num);
      _number->show();
      _labelNumber->show();
      _labelNumber->setText("Number of Pixels");
      break;
    case 1:
      filters = Filter::gaussian(num);
      _number->show();
      _labelNumber->show();
      _labelNumber->setText("Coefficient");
      break;
    case 2:
      filters = Filter::prewitt(num);
      _number->show();
      _labelNumber->show();
      _labelNumber->setText("Number of Pixels");
      break;
    default:
      filters = _filters[_blurChoices->currentIndex()];
      _number->hide();
      _labelNumber->hide();
  }
  
  if(_blurChoices->currentIndex() > 5)
    _deleteButton->setEnabled(true);
  else
    _deleteButton->setEnabled(false);
  
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
  
  _filterView->resizeColumnsToContents();
  _filterView->resizeRowsToContents();
}
