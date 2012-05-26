#include "FilterEditorItem.h"

#include <QLineEdit>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QMdiArea>
#include <QtGui/QPushButton>

#include <QTimer>
#include <QFile>
#include <QtXml/QDomDocument>
#include <QtXml/QDomImplementation>
#include <QtXml/QDomElement>
#include <QTextStream>

using namespace filtrme;
using namespace imagein::algorithm;

FilterEditorItem::FilterEditorItem()
{
  _width = 3;
  _height = 3;
  initUI();
}


void FilterEditorItem::initUI()
{
  QSpinBox *spinBoxWidth;
  QSpinBox *spinBoxHeight;
  QLabel *label;
  QLabel *label_2;

  _filter = new QTableWidget(_width, _height, this);
  _filter->setGeometry(QRect(210, 60, 350, 260));
  _filter->resizeColumnsToContents();
  _filter->resizeRowsToContents();
  
  int w = 0,  h = 0;  
  for(int i = 0 ; i < _filter->rowCount(); i++)  
    h += _filter->rowHeight(i);  
  for(int i = 0 ; i < _filter->columnCount(); i++)  
    w += _filter->columnWidth(i);  

  _filter->setMinimumSize(w, h);  
  
  spinBoxWidth = new QSpinBox(this);
  spinBoxWidth->setGeometry(QRect(100, 167, 60, 27));
  spinBoxWidth->setValue(_width);
  spinBoxWidth->setMinimum(2);
  spinBoxHeight = new QSpinBox(this);
  spinBoxHeight->setGeometry(QRect(100, 207, 60, 27));
  spinBoxHeight->setValue(_height);
  spinBoxHeight->setMinimum(2);
  label = new QLabel(this);
  label->setText("Width:");
  label->setGeometry(QRect(30, 170, 66, 17));
  label_2 = new QLabel(this);
  label_2->setText("Height:");
  label_2->setGeometry(QRect(30, 210, 66, 17));

  this->setMinimumSize(600, 330);

  QObject::connect(spinBoxWidth, SIGNAL(valueChanged(int)), this, SLOT(widthChanged(int)));
  QObject::connect(spinBoxHeight, SIGNAL(valueChanged(int)), this, SLOT(heightChanged(int)));
  QObject::connect(this, SIGNAL(insertRow(int)), _filter, SLOT(insertRow(int)));
  QObject::connect(this, SIGNAL(removeRow(int)), _filter, SLOT(removeRow(int)));
  QObject::connect(this, SIGNAL(insertColumn(int)), _filter, SLOT(insertColumn(int)));
  QObject::connect(this, SIGNAL(removeColumn(int)), _filter, SLOT(removeColumn(int)));

}

void FilterEditorItem::widthChanged(const int width)
{
  if(_width < width)
    emit(insertColumn(width-_width));
  else
    emit(removeColumn(_width-width));
    
  _width = width;
  _filter->resizeColumnsToContents();
}

void FilterEditorItem::heightChanged(const int height)
{
  if(_height < height)
    emit(insertRow(height-_height));
  else
    emit(removeRow(_height-height));
  
  _height = height;
  _filter->resizeRowsToContents();
}

imagein::algorithm::Filter* FilterEditorItem::validFilter()
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
        
      if(ok)
        (*filter)[w][h] = i;
    }
    if(!ok)
      break;
  }
  if(!ok)
    filter = NULL;
  
  return filter;
}
