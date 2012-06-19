/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FILTER_H
#define FILTER_H

#include <iostream>
#include <utility>
#include <vector>

namespace imagein
{
	namespace algorithm
	{
		class Filter
		{
		private:
		  class Line
		  {
		  public:
			Line (int i, Filter& m);

			int& operator[] (int i);

		  private:
			int _width;
			int* _rry;
		  };

		public:
		  class iterator
		  {
        friend class Filter;

        public:
        iterator operator++ ();
        int& operator* ();
        bool operator !=(Filter::iterator it);
        std::pair<int, int> pos ();

        private:
        iterator (Filter& m);

        Filter& _Filter;
        int _i;
        int _j;
		  };

		  Filter (int w, int h);
		  Filter (const Filter& m);
		  virtual ~Filter ();

		  iterator begin();
		  iterator end();

		  inline int width() { return _width; }
		  inline int height() { return _height; }

		  Line operator[] (int i);
      
      static std::vector<Filter*> uniform(int numPixels);
			static std::vector<Filter*> gaussian(double alpha);
			static std::vector<Filter*> prewitt(int numPixels);
			static std::vector<Filter*> roberts();
			static std::vector<Filter*> sobel();
			static std::vector<Filter*> squareLaplacien();
      
		private:
		  int _width;
		  int _height;
		  int* _mtrx;

		};

		class invalid_filter : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Invalid size : expect to be odd.";
			}
		};
	}
}

#endif //FILTER_H
