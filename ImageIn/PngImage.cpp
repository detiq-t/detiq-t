#include "PngImage.h"

#include "ImageFileException.h"

using namespace imagein;
using namespace std;

PngImage::PngImage(string filename)
 : ImageFile(filename), _was_palette(false)
{
    _source = new ifstream(filename.c_str(), ios_base::in | ios_base::binary);

    //Allocate a buffer of 8 bytes, where we can put the file signature.
    png_byte pngsig[8];

    //Read the 8 bytes from the stream into the sig buffer.
    _source->read((char*)pngsig, 8);

    //Check if the read worked...
    if (!_source->good()) {
        throw ImageFileException("File "+filename+" is not a valid png file", __LINE__, __FILE__);
    }

    //Let LibPNG check the sig. If this function returns 0, everything is OK.
    if(png_sig_cmp(pngsig, 0, 8) != 0) {
        throw ImageFileException("File "+filename+" is not a valid png file", __LINE__, __FILE__);
    }

    _pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!_pngPtr) {
        throw ImageFileException("Couldn't initialize png read struct", __LINE__, __FILE__);
    }

    _infoPtr = png_create_info_struct(_pngPtr);
    if (!_infoPtr) {
        png_destroy_read_struct(&_pngPtr, (png_infopp)0, (png_infopp)0);
        throw ImageFileException("Couldn't initialize png info struct", __LINE__, __FILE__);
    }

    //custom read function
    png_set_read_fn(_pngPtr,(png_voidp)_source, userReadData);

    //read the header.
    //Set the amount signature bytes we've already read:
    png_set_sig_bytes(_pngPtr, 8);

    //Now call png_read_info with our pngPtr as image handle, and infoPtr to receive the file info.
    png_read_info(_pngPtr, _infoPtr);

    //If the data is contained in a palette, convert it to RGB
    if (png_get_color_type(_pngPtr, _infoPtr) == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(_pngPtr);
        _was_palette = true;
    }
}

unsigned int PngImage::readHeight()
{
    return png_get_image_height(_pngPtr, _infoPtr);
}

unsigned int PngImage::readWidth()
{
    return png_get_image_width(_pngPtr, _infoPtr);
}

unsigned int PngImage::readNbChannels()
{
    return (_was_palette) ? 3 : png_get_channels(_pngPtr, _infoPtr);
}

unsigned int PngImage::readDepth()
{
    return png_get_bit_depth(_pngPtr, _infoPtr);
}

char* PngImage::readData()
{


    return NULL;
}

void PngImage::writeData(char* data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth){
    //TODO
}
