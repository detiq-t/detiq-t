/*!
 * \brief Crops the image to the boundaries defined by a Rectangle.
 *
 * \param rect the rectangle used to define the boundaries of the new image.
 * \return A new image of the same type.
 */
Image<D> crop(const Rectangle& rect) const;

template<typename D>
Image<D> Image<D>::crop(const Rectangle& rect) const
{
    unsigned int topleft = rect.y*_width + rect.x;

    Image<D>::const_iterator it = this->begin() + topleft*_nChannels; //iterator pointing on the top-left corner of the rectangle
    Image<D>::const_iterator end = it + ((rect.h-1)*_width + rect.w)*_nChannels; //iterator pointing just after the bottom-right corner of the rectangle

    D* data = new D[rect.w * rect.y * _nChannels]; //new array containing the new image data
    D* di = data; //pointer to the first element of data

    unsigned int columnNo = 0;

    while(it < end) {
        *di = *it;
        ++di;
        ++it;

        if(++columnNo == rect.w) {
            it += (_width-rect.w) * _nChannels;
            columnNo = 0;
        }
    }

    //creating an empty image then filling its attributes manually avoids a copy of every value in the data array.
    Image<D> ret;
    ret._width = rect.w;
    ret._height = rect.h;
    ret._nChannels = this->_nChannels;
    ret._mat = data;

    return ret;
}
