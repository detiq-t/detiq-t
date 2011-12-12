#ifndef ARRAY_H
#define ARRAY_H


namespace ImageIn
{
    class Array
    {
        public:
            typedef unsigned int* iterator;
            Array() {}
            virtual ~Array() {}
            unsigned int getWidth() const { return _width; }
            unsigned int operator[](unsigned int index) const { return _array[index]; };
            unsigned int& operator[](unsigned int index) { return _array[index]; };
            iterator begin() { return _array; };
            iterator end() { return _array+_width; };

        protected:
        private:
            unsigned int* _array;
            unsigned int _width;
    };
}

#endif // ARRAY_H
