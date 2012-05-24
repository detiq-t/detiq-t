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
