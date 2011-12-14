#ifndef ARRAY_H
#define ARRAY_H


namespace imagein
{
    class Array
    {
        public:
            typedef unsigned int* iterator;
            typedef const unsigned int* const_iterator;

            inline Array(int width = 0) : _width(width) { _array = new unsigned int[width]; }
            inline virtual ~Array() { delete[] _array; }

            inline unsigned int getWidth() const { return _width; }
            inline unsigned int operator[](unsigned int index) const { return _array[index]; };
            inline unsigned int& operator[](unsigned int index) { return _array[index]; };

            inline iterator begin() { return _array; };
            inline const_iterator begin() const { return _array; };
            inline iterator end() { return _array+_width; };
            inline const_iterator end() const { return _array+_width; };

        protected:
        private:
            unsigned int* _array;
            unsigned int _width;
    };
}

#endif // ARRAY_H
