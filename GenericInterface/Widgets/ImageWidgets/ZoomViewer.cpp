#include "ZoomViewer.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <sstream>

using namespace std;
using namespace imagein;
using namespace genericinterface;

ZoomViewer::ZoomViewer(Image* im, int row, int col) : QGraphicsScene(0, 0, row * PIXEL_S, col * PIXEL_S),
                                          _image(im), _row(row), _col(col), _channel(0)
{
  _rects = new QGraphicsRectItem[row * col];
  _texts = new QGraphicsTextItem[row * col];

  for(int i = 0; i < _row; i++)
  {
    for(int j = 0; j < _col; j++)
    {
      QGraphicsRectItem& r = at(i, j);
      r.setRect(i * PIXEL_S, j * PIXEL_S, PIXEL_S, PIXEL_S);

      QGraphicsTextItem& t = atText(i, j);
      t.setPlainText("");
      t.setScale(0.7);
      t.setPos(i * PIXEL_S, j * PIXEL_S);

      addItem(&r);
      addItem(&t);
    }
  }
  
  draw(0, 0);
}

void ZoomViewer::draw(int x, int y)
{
  static int ox(0), oy(0);

  if (x < 0 || y < 0) {
    x = ox;
    y = oy;
  } else {
    ox = x;
    oy = y;
  }

  for(int i = 0; i < _row; i++)
  {
    for(int j = 0; j < _col; j++)
    {
      QGraphicsRectItem& r = at(i, j);

      int px = i + x;
      int py = j + y;


      if(   px < static_cast<int>(_image->getWidth())
         && py < static_cast<int>(_image->getHeight()))
      {
        /* We are in the image */

        try
        {
          int red;
          int green;
          int blue;

          int v(_image->getPixel(px, py, _channel));

          if(_image->getNbChannels() == 3)
          {
            red = _image->getPixel(px, py, 0);
            green = _image->getPixel(px, py, 1);
            blue = _image->getPixel(px, py, 2);
          }
          else
          {
            red = _image->getPixel(px, py, 0);
            green = _image->getPixel(px, py, 0);
            blue = _image->getPixel(px, py, 0);
          }

          ostringstream s;
          s << v;
          atText(i, j).setPlainText(QString(s.str().c_str()));

          if (red + blue + green > 127 * 3) {
            atText(i,j).setDefaultTextColor(Qt::black);
          } else {
            atText(i,j).setDefaultTextColor(Qt::white);
          }
          
          QColor color(red, green, blue);
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

void ZoomViewer::channelChosen(int c)
{
  _channel = c;
  draw();
}

QGraphicsRectItem& ZoomViewer::at(int i, int j)
{
  return _rects[j * _row + i];
}

QGraphicsTextItem& ZoomViewer::atText(int i, int j)
{
  return _texts[j * _row + i];
}
