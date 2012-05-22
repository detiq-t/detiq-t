#include "StructElemViewer.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <sstream>

using namespace std;
using namespace imagein;

StructElemViewer::StructElemViewer(const MorphoMat::StructElem<depth_default_t>& elem) 
: QGraphicsScene(0, 0, elem.getElem().getWidth() * PIXEL_S * elem.getScale(), elem.getElem().getHeight() * PIXEL_S*elem.getScale()),
  _image(elem.getElem()),_col(elem.getElem().getHeight()*elem.getScale()), _row(elem.getElem().getWidth()*elem.getScale()),  _scale(elem.getScale())
{
  _rects = new QGraphicsRectItem[_row * _col];

  for(int i = 0; i < _row; i++)
  {
    for(int j = 0; j < _col; j++)
    {
      QGraphicsRectItem& r = at(i, j);
      r.setRect(i * PIXEL_S, j * PIXEL_S, PIXEL_S, PIXEL_S);


      addItem(&r);
    }
  }
}

StructElemViewer::~StructElemViewer() {
    delete[] _rects;
}

void StructElemViewer::draw(int x, int y)
{
  for(int i = 0; i < _row; i++)
  {
    for(int j = 0; j < _col; j++)
    {
      QGraphicsRectItem& r = at(i, j);

      int px = (i + x)/_scale;
      int py = (j + y)/_scale;


      if(   px < static_cast<int>(_image.getWidth())
         && py < static_cast<int>(_image.getHeight()))
      {
        /* We are in the image */

        try
        {

          unsigned char value = _image.getPixel(px, py) ? 32 : 224;

          
          QColor color(value, value, value);
          QBrush brush(color, Qt::SolidPattern);

          r.setBrush(brush);
        } catch(...)
        {
          std::cerr << "invalid operation on Image struct" << std::endl;
        }
      }
    }
  }
}

QGraphicsRectItem& StructElemViewer::at(int i, int j)
{
  return _rects[j * _row + i];
}

