#include "ZoomViewer.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <sstream>

using namespace std;
using namespace imagein;
using namespace genericinterface;

ZoomViewer::ZoomViewer(Image* im, int row, int col) : QGraphicsScene(0, 0, row * PIXEL_S, col * PIXEL_S),
                                          _image(im), _row(row), _col(col)
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
      t.setPos(i * PIXEL_S, j * PIXEL_S);

      addItem(&r);
      addItem(&t);
    }
  }
}

void ZoomViewer::draw(int x, int y)
{
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
          int red = _image->getPixel(px, py, 0);
          int green = _image->getPixel(px, py, 1);
          int blue = _image->getPixel(px, py, 2);

          if (red == green && green == blue)
          {
            ostringstream s;
            s << red;
            atText(i, j).setPlainText(QString(s.str().c_str()));

            if (red > 127)
              atText(i,j).setDefaultTextColor(Qt::black);
            else
              atText(i,j).setDefaultTextColor(Qt::white);
          }
          else
          {
            ostringstream s;
            s << red << endl << green << endl << blue;
            atText(i, j).setPlainText(QString(s.str().c_str()));

            if ((red + green + blue) / 3 > 127)
              atText(i,j).setDefaultTextColor(Qt::black);
            else
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

QGraphicsRectItem& ZoomViewer::at(int i, int j)
{
  return _rects[j * _row + i];
}

QGraphicsTextItem& ZoomViewer::atText(int i, int j)
{
  return _texts[j * _row + i];
}
