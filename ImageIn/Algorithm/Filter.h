#include <iostream>
#include <utility>

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
		  Filter (Filter& m);
		  virtual ~Filter ();

		  iterator begin();
		  iterator end();

		  inline int width() { return _width; }
		  inline int height() { return _height; }

		  Line operator[] (int i);

		private:
		  int _height;
		  int _width;
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
