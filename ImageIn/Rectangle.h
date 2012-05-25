#ifndef RECTANGLE_H
#define RECTANGLE_H


namespace imagein
{
    /*!
     * \brief Class used to represent a portion of an image.
     *
     * This class is used as a parameter for various algorithm and Image methods. It defines a rectangle, portion of an image, by its top-left corner and
     * its width and height.
     *
     * A rectangle with all its attributes to zero means the whole image.
     */
    struct Rectangle
    {
        unsigned int x, y;
        unsigned int w, h;
        Rectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h) : x(x), y(y), w(w), h(h) {}
        Rectangle() : x(0), y(0), w(0), h(0) {}
        Rectangle(const imagein::Rectangle& r) : x(r.x), y(r.y), w(r.w), h(r.h) {}
    };
}

#endif // RECTANGLE_H
