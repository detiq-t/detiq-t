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
