#include "Filter.h"

using namespace std;

Filter::Filter (int w, int h) : _height (h), _width (w)
{
  if(w % 2 != 0 || h % 2 != 0)
	throw invalid_filter();
  _mtrx = new int[h * w];
}

Filter::Filter (Filter& m) : _width (m._width), _height (m._height)
{
  if(_width % 2 != 0 || _height % 2 != 0)
	throw invalid_filter();
	
  _mtrx = new int [_width * _height];

  for(int i = 0; i < _width * _height; i++)
    _mtrx[i] = m._mtrx[i];
}

Filter::~Filter ()
{
  delete[] _mtrx;
}

Filter::Line Filter::operator[] (int i)
{
  return Line (i, *this);
}

Filter::Line::Line (int i, Filter& m) : _width (m._width)
{
  _rry = m._mtrx + i * m._height;
}

int& Filter::Line::operator[] (int i)
{
  return *(_rry + i);
}

Filter::iterator Filter::begin ()
{
  return iterator (*this);
}

Filter::iterator Filter::end ()
{
  Filter::iterator it (*this);
  it._j = -1;
  it._i = -1;

  return it;
}

Filter::iterator::iterator (Filter& m) : _Filter (m), _i (0), _j (0)
{
}

Filter::iterator Filter::iterator::operator++ ()
{
  Filter::iterator res (*this);

  _i++;

  if (_i == _Filter.width())
  {
    _i = 0;
    _j++;
  }

  if (_j == _Filter.height())
  {
    _i = -1;
    _j = -1;
  }
  
  return res;
}

int& Filter::iterator::operator* ()
{
  return _Filter[_i][_j];
}

bool Filter::iterator::operator!= (iterator it)
{
  return _i != it._i || _j != it._j;
}

std::pair<int, int> Filter::iterator::pos ()
{
  return make_pair (_i, _j);
}
