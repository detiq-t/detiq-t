#include "FilterEditor.h"

#include <QLineEdit>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QMdiArea>
#include <QtGui/QPushButton>

#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomImplementation>
#include <QtXml/QDomElement>
#include <QTextStream>

using namespace filtrme;
using namespace imagein::algorithm;

FilterEditor::FilterEditor()
{
  _width = 3;
  _height = 3;
  initUI();
}


void FilterEditor::initUI()
{  
  QDialogButtonBox *buttonBox;
  QSpinBox *spinBoxWidth;
  QSpinBox *spinBoxHeight;
  QLabel *label;
  QLabel *label_2;
  QLabel *label_3;

  buttonBox = new QDialogButtonBox(this);
  buttonBox->setGeometry(QRect(140, 290, 341, 32));
  buttonBox->setOrientation(Qt::Horizontal);
  buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
  QPushButton* applyButton = buttonBox->addButton(QString::fromStdString("Apply"), QDialogButtonBox::ApplyRole);
  _filter = new QTableWidget(_width, _height, this);
  _filter->setGeometry(QRect(210, 20, 271, 241));
  _filter->resizeColumnsToContents();
  _filter->resizeRowsToContents();
  spinBoxWidth = new QSpinBox(this);
  spinBoxWidth->setGeometry(QRect(100, 90, 60, 27));
  spinBoxWidth->setValue(_width);
  spinBoxWidth->setMinimum(2);
  spinBoxHeight = new QSpinBox(this);
  spinBoxHeight->setGeometry(QRect(100, 130, 60, 27));
  spinBoxHeight->setValue(_height);
  spinBoxHeight->setMinimum(2);
  label = new QLabel(this);
  label->setGeometry(QRect(30, 90, 66, 17));
  label_2 = new QLabel(this);
  label_2->setGeometry(QRect(30, 130, 66, 17));
  label_3 = new QLabel(this);
  label_3->setGeometry(QRect(10, 40, 66, 17));
  _name = new QLineEdit(this);
  _name->setGeometry(QRect(70, 30, 113, 27));

  QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(save()));
  QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));
  QObject::connect(applyButton, SIGNAL(clicked()), this, SLOT(apply()));
  QObject::connect(spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(widthChanged(int)));
  QObject::connect(spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(heightChanged(int)));
  QObject::connect(this, SIGNAL(insertRow(int)), _filter, SLOT(insertRow(int)));
  QObject::connect(this, SIGNAL(removeRow(int)), _filter, SLOT(removeRow(int)));
  QObject::connect(this, SIGNAL(insertColumn(int)), _filter, SLOT(insertColumn(int)));
  QObject::connect(this, SIGNAL(removeColumn(int)), _filter, SLOT(removeColumn(int)));

  label->setText("Width:");
  label_2->setText("Height:");
  label_3->setText("Name:");
  
  this->adjustSize();
  this->resize(500, 337);
  this->setWindowTitle("FilterEditor");
}

void FilterEditor::save()
{
  Filter* filter = NULL;
  if(_name->text() == "")
  {
    QMessageBox msgBox(QMessageBox::Critical, "Error!", "Your filter has to have a name to be saved.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
    return;
  }
  if((filter = validFilter()) != NULL)
    saveXML(filter);
}

void FilterEditor::saveXML(Filter* filterToSave)
{
  QFile file("filters.xml");
  // document
  QDomImplementation impl = QDomDocument().implementation();
  // document with document type
  QString name = "Filters";
  QString publicId = "-//Detiq-T//DTD Filters 1.0 //EN";
  QString systemId = "Detiq-T/DTD/filter.dtd";
  QDomDocument doc(impl.createDocumentType(name,publicId,systemId));
  QDomNode oldFilter;
  bool replace = false;
  
  if(!file.exists())
  {
    // add some XML comment at the beginning
    doc.appendChild(doc.createComment("This file contains filters"));
    doc.appendChild(doc.createTextNode("\n")); // for nicer output
    QDomElement e = doc.createElement("filtersList");
    doc.appendChild(e);
    std::cout << doc.toString().toStdString();
  }
  else
  {
    file.open(QIODevice::ReadOnly);
	  doc.setContent(&file);
	  file.close();
    
    QDomElement root = doc.documentElement();
    QDomNode child = root.firstChild();
	  while(!child.isNull())
	  {
      QDomElement e = child.toElement();
	    // We know how to treat appearance and geometry
	    if (e.attribute("name") == _name->text())
	    {
	      QMessageBox msgBox(QMessageBox::Warning, "Warning!", "This filter name is already use.");
        msgBox.setInformativeText("Do you want to replace it?");
        msgBox.setStandardButtons(QMessageBox::No|QMessageBox::Yes);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
        {
          oldFilter = e;
          replace = true;
        }
        else
          return;
      }
      child = child.nextSibling();
	  }
    
    std::cout << doc.toString().toStdString();
  }

  // root node
  QDomElement filterNode = doc.createElement("filter");
  filterNode.setAttribute("name", _name->text());
  filterNode.setAttribute("width", QString::number(_width));
  filterNode.setAttribute("height", QString::number(_height));

  // values
  QDomElement valuesNode = doc.createElement("values");

  QString s = "";
  for(int w = 0; w < _width; w++)
  {
    for(int h = 0; h < _height; h++)
    {
      s += QString::number((*filterToSave)[w][h]);
      if(w != _width - 1 || h != _height - 1)
        s += " ";
    }
  }
  valuesNode.appendChild(doc.createTextNode(s));
  filterNode.appendChild(valuesNode);
  if(replace)
    doc.documentElement().replaceChild(filterNode, oldFilter);
  else
    doc.documentElement().appendChild(filterNode);
  
  if(file.open(QFile::WriteOnly))
  {
    QTextStream out(&file);
    out << doc.toString();
    file.close();
  }
}

void FilterEditor::cancel()
{
  QMessageBox msgBox(QMessageBox::Warning, "Warning!", "Unsaved changes will be lost.");
  msgBox.setInformativeText("Do you want to continue?");
  msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
  msgBox.setDefaultButton(QMessageBox::No);
  int ret = msgBox.exec();
  if(ret == QMessageBox::Yes)
    emit(cancelAction());
}

void FilterEditor::apply()
{
  Filter* filter = NULL;
  if((filter = validFilter()) != NULL)
    emit(applyFiltering(new Filtering(filter)));
}

void FilterEditor::widthChanged(const int width)
{
  if(_width < width)
    emit(insertRow(width-_width));
  else
    emit(removeRow(_width-width));
    
  _width = width;
}

void FilterEditor::heightChanged(const int height)
{
  if(_height < height)
    emit(insertColumn(height-_height));
  else
    emit(removeColumn(_height-height));
  
  _height = height;
}

imagein::algorithm::Filter* FilterEditor::validFilter()
{
  Filter* filter = new Filter(_width, _height);
  bool ok;
  for(int w = 0; w < _width; w++)
  {
    for(int h = 0; h < _height; h++)
    {
      int i;
      QTableWidgetItem* item = _filter->item(w, h);
      if(!item)
        ok = false;
      else
        i = item->text().toInt(&ok);
      if(!ok)
      {
        QMessageBox msgBox(QMessageBox::Critical, "Error!", "Every square have to be completed by int value.");
        std::ostringstream oss;
        oss << w;
        std::string ws = oss.str();
        oss.str("");
        oss << h;
        std::string hs = oss.str();
        msgBox.setInformativeText(QString::fromStdString("Square " + ws + ";" + hs + "isn't int."));
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        break;
        ok = true;
      }
      else
      {
        (*filter)[w][h] = i;
      }
    }
    if(!ok)
      break;
  }
  if(!ok)
    filter = NULL;
  
  return filter;
}
