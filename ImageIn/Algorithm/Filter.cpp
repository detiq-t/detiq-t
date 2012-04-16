#include "Filter.h"
#include <cmath>

using namespace std;
using namespace imagein;
using namespace algorithm;

Filter::Filter (int w, int h) : _height (h), _width (w)
{
  if(w % 2 != 1 || h % 2 != 1)
	throw invalid_filter();
  _mtrx = new int[h * w];
}

Filter::Filter (const Filter& m) : _width (m._width), _height (m._height)
{
  if(_width % 2 != 1 || _height % 2 != 1)
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

std::vector<Filter*> Filter::uniform(int coef = 1, int numPixels = 3)
{
  Filter* filter = new Filter(numPixels, numPixels);
  for(int i = 0; i < numPixels; i++)
  {
    for(int j = 0; j < numPixels; j++)
    {
      (*filter)[i][j] = coef;
    }
  }
  std::vector<Filter*> filters;
  filters.push_back(filter);
  return filters;
}

std::vector<Filter*> Filter::gaussian(double alpha)
{
  std::vector<double> gaussCoef;
  double min(0);

  for (int i = 0; ; i++)
  {
  double coef = 10000.0 * std::exp(-(std::pow(i, 2.0)) / (2.0 * std::pow(alpha, 2))) / (2 * M_PI * std::pow(alpha, 2));
  if (i == 0) min = coef / 10 + 1;
  if (coef < min)
    break;
  else
    gaussCoef.push_back(coef);
  }

  std::cout << gaussCoef.size() * 2 - 1 << std::endl;

  Filter* f = new Filter(gaussCoef.size() * 2 - 1, gaussCoef.size() * 2 - 1);
  int center = gaussCoef.size() - 1;

  for(unsigned int i = 0; i < gaussCoef.size(); i++)
  {
    for(unsigned int j = i; j < gaussCoef.size(); j++)
    {
      if(i == 0) /* values are already in gaussCoef, so no compute needed */
      {
        (*f)[center][center + j] = gaussCoef[j];

        if(j != 0)
        {
          (*f)[center][center - j] = gaussCoef[j];
          (*f)[center - j][center] = gaussCoef[j];
          (*f)[center + j][center] = gaussCoef[j];
        }
      }
      else
      {
        double coef = 10000.0 * std::exp(-(std::pow(i, 2) + std::pow(j, 2)) / (2 * std::pow(alpha, 2))) / (2 * M_PI * std::pow(alpha, 2));

        (*f)[center + i][center + j] = coef;
        (*f)[center + i][center - j] = coef;
        (*f)[center - i][center + j] = coef;
        (*f)[center - i][center - j] = coef;
        (*f)[center + j][center + i] = coef;
        (*f)[center + j][center - i] = coef;
        (*f)[center - j][center + i] = coef;
        (*f)[center - j][center - i] = coef;
      } 
    }
  }
  std::vector<Filter*> filters;
  filters.push_back(f);
  return filters;
}

std::vector<Filter*> Filter::prewitt(int coef = 1, int numPixels = 3)
{
  std::vector<Filter*> filters;
  
  for(int vertical = 1 ; vertical >= 0 ; --vertical)
  {
    int width = 3, height = 3;
    
    if(vertical == 1) height = numPixels;
    else width = numPixels;
    
    Filter* filter = new Filter(width, height);
    for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
      {
        if((vertical == 1 && i == 0) || (vertical == 0 && j == 0))
          (*filter)[i][j] = -coef;
        else if((vertical == 1 && i == width - 1) || (vertical == 0 && j == height - 1))
          (*filter)[i][j] = coef;
        else
          (*filter)[i][j] = 0;
      }
    }
    filters.push_back(filter);
  }
  return filters;
}

std::vector<Filter*> Filter::roberts(int coef = 1)
{
  std::vector<Filter*> filters;
  
  for(int h = 1 ; h >= 0 ; --h)
  {				
    Filter* filter = new Filter(3, 3);
    for(int i = 0; i < 3; ++i)
    {
      for(int j = 0; j < 3; ++j)
      {
        if((h == 1 && i == 1 && j == 2) || (h == 0 && i == 1 && j == 1))
          (*filter)[i][j] = -coef;
        else if((h == 1 && i == 2 && j == 1) || (h == 0 && i == 2 && j == 2))
          (*filter)[i][j] = coef;
        else
          (*filter)[i][j] = 0;
      }
    }
    filters.push_back(filter);
  }
  
  return filters;
}

std::vector<Filter*> Filter::sobel(int coef = 1)
{
  std::vector<Filter*> filters;
  
  for(int vertical = 1 ; vertical >= 0 ; --vertical)
  {
    int width = 3, height = 3;
    
    Filter* filter = new Filter(width, height);
    for(int i = 0; i < width; i++)
    {
      for(int j = 0; j < height; j++)
      {
        if(vertical == 1)
        {
          if(i == 0)
            if(j == 1) (*filter)[i][j] = -(2 * coef);
            else (*filter)[i][j] = -coef;
          else if(i == 2)
            if(j == 1) (*filter)[i][j] = 2 * coef;
            else (*filter)[i][j] = coef;
          else (*filter)[i][j] = 0; 
        }
        else
        {
          if(j == 0)
            if(i == 1) (*filter)[i][j] = -(2 * coef);
            else (*filter)[i][j] = -coef;
          else if(j == 2)
            if(i == 1) (*filter)[i][j] = 2 * coef;
            else (*filter)[i][j] = coef;
          else (*filter)[i][j] = 0;
        }
      }
    }
    filters.push_back(filter);
  }
  return filters;
}
