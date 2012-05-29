#include "StructElemViewer.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <sstream>

using namespace std;
using namespace imagein;

StructElemViewer::StructElemViewer(MorphoMat::StructElem<depth_default_t>& elem) 
: QGraphicsScene(0, 0, elem.getWidth() * PIXEL_S * elem.getScale(), elem.getHeight() * PIXEL_S*elem.getScale()),
  _image(elem),  _scale(elem.getScale()), _row(elem.getWidth()*elem.getScale()), _col(elem.getHeight()*elem.getScale()) {
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

void StructElemViewer::mousePressEvent (QGraphicsSceneMouseEvent* event) 
{
    QPointF point = event->scenePos(); // Get the location of the click
    unsigned int px = (point.x()/PIXEL_S)/_scale;
    unsigned int py = (point.y()/PIXEL_S)/_scale;
    if(px < _image.getWidth() && py < _image.getHeight()) {
        if(event->button()==Qt::LeftButton) {
            _image.setPixel(px, py, !_image.getPixel(px, py));  
        }
        else if(event->button() == Qt::RightButton) {
            _image.setCenter(px, py);
        }
    }
    //std::cout << px << ":" << py << std::endl;
    this->draw(0,0);
}
                    

void StructElemViewer::draw(int x, int y)
{
  for(int i = 0; i < _row; i++)
  {
    for(int j = 0; j < _col; j++)
    {
      QGraphicsRectItem& r = at(i, j);

      unsigned int px = (i + x)/_scale;
      unsigned int py = (j + y)/_scale;


      if(   px < static_cast<int>(_image.getWidth())
         && py < static_cast<int>(_image.getHeight()))
      {
        /* We are in the image */

        try
        {
          QColor high, low;

          if(px == _image.getWidth()/2 || (_image.getWidth()%2==0 && (px == _image.getWidth()/2-1))
          || py == _image.getHeight()/2 || (_image.getHeight()%2==0 && (py == _image.getHeight()/2-1))) {
            high = QColor(232, 232, 232);
            low = QColor(24, 24, 24);
          }
          else {
            high = QColor(224, 224, 224);
            low = QColor(32, 32, 32);
          }
          if(px == _image.getCenterX() && py == _image.getCenterY()) {
            high = QColor(200, 192, 192);
            low = QColor(8, 0, 0);
          }

          
          QColor color = _image.getPixel(px, py) ? low : high;

          QBrush brush;
          QBrush(color, Qt::SolidPattern);
          if(px == _image.getCenterX() && py == _image.getCenterY()) {
            brush = QBrush(color, Qt::SolidPattern);
          }
          else {
            brush = QBrush(color, Qt::SolidPattern);
          }

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

