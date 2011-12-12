#ifndef RECTANGLE_H
#define RECTANGLE_H


namespace ImageIn
{
    struct Rectangle
    {
        unsigned int x, y;
        unsigned int w, h;
        Rectangle(unsigned int x_, unsigned int y_, unsigned int w_, unsigned int h_) : x(x_), y(y_), w(w_), h(h_) {}
        Rectangle() : x(0), y(0), w(0), h(0) {}
    };
}

#endif // RECTANGLE_H
