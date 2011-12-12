#include "Image.h"

using namespace ImageIn;


template <typename D>
Image<D>::~Image()
{
    //dtor
}

template <typename D>
Image<D>::Image(const Image& other)
{
    //copy ctor
}

template <typename D>
Image<D>& Image<D>::operator=(const Image& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
