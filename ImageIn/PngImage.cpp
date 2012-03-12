#include "PngImage.h"

#include "mystdint.h"

#include "ImageFileException.h"

using namespace imagein;
using namespace std;

//TODO : error handling.

PngImage::PngImage(string filename)
 : ImageFile(filename), _readPngPtr(NULL), _writePngPtr(NULL), _readInfoPtr(NULL), _writeInfoPtr(NULL), _stream(NULL), _was_palette(false)
{

}

PngImage::~PngImage()
{
    delete _stream;

    if(_readPngPtr) {
        png_destroy_read_struct(&_readPngPtr, &_readInfoPtr,(png_infopp)0);
    }

    if(_writePngPtr) {
        png_destroy_write_struct(&_writePngPtr, (png_infopp)&_writeInfoPtr);
    }
}

void* PngImage::readData()
{
    if(!_readPngPtr) {
        initRead();
    }

    unsigned int w=readWidth(), h=readHeight(), c=readNbChannels(), d=readDepth();
       
    //handle depths other than 8-13-24-32
    if (d <= 8)
        d = 8;
    else if (d <= 16)
        d = 16;
    else if (d <= 24)
        d = 24;
    else
        d = 32;
 
    png_bytep data = new png_byte[ w * h * c * d/8]; //The actual array that will contain the data
    png_bytep* rowPtrs = new png_bytep[h];
    unsigned int rowSize = w*c*d/8;

    for (size_t i = 0; i < h; ++i) {
        rowPtrs[i] = data + i*rowSize;
    }
    //now rowPtrs is an array of pointers, pointing on the beginning of each row

    //we can read the image.
    png_read_image(_readPngPtr, rowPtrs);

    delete[] rowPtrs;

    return data;
}

void PngImage::writeData(const void* const data_, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{
	const uint8_t* const data = reinterpret_cast<const uint8_t* const>(data_);
	
    if(!_writePngPtr) {
        initWrite();
    }

    //set the color type
    int colorType;
    switch(nChannels) {
        case 1:
            colorType = PNG_COLOR_TYPE_GRAY;
            break;
        case 2:
            colorType = PNG_COLOR_TYPE_GRAY_ALPHA;
            break;
        case 3:
            colorType = PNG_COLOR_TYPE_RGB;
            break;
        case 4:
            colorType = PNG_COLOR_TYPE_RGB_ALPHA;
            break;
        default:
            throw ImageFileException("Unexpected number of channels for png file", __LINE__, __FILE__);
    }

    //General infos on the file.
    png_set_IHDR(_writePngPtr, _writeInfoPtr, width, height,
       depth, colorType, PNG_INTERLACE_NONE,
       PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    //write file header
    png_write_info(_writePngPtr, _writeInfoPtr);

    //preparing data
    png_bytep rowPtr;
    unsigned int rowSize = width*nChannels*depth/8;

    for (size_t i = 0; i < height; ++i) {
        rowPtr = (png_bytep)data + i*rowSize;
        png_write_row(_writePngPtr, rowPtr);
    }

    //then the end of the file.
    png_write_end(_writePngPtr, _writeInfoPtr);
}

void PngImage::initRead()
{
    //create reading stream if it doesn't exists
    if(!_stream) {
        _stream = new fstream(_filename.c_str(), ios_base::in | ios_base::out | ios_base::binary);
    }

    //Allocate a buffer of 8 bytes, where we can put the file signature.
    png_byte pngsig[8];

    //Read the 8 bytes from the stream into the sig buffer.
    _stream->read((char*)pngsig, 8);

    //Check if the read worked and if the file is a valid png image.
    if (!(_stream->good() && png_sig_cmp(pngsig, 0, 8) == 0)) {
        throw ImageFileException("File "+_filename+" is not a valid png file", __LINE__, __FILE__);
    }

    //TODO : error handling
    _readPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)_errorPtr, userErrorHandler, userErrorHandler);
    if (!_readPngPtr) {
        throw ImageFileException("Couldn't initialize png read struct", __LINE__, __FILE__);
    }

    _readInfoPtr = png_create_info_struct(_readPngPtr);
    if (!_readInfoPtr) {
        png_destroy_read_struct(&_readPngPtr, (png_infopp)0, (png_infopp)0);
        throw ImageFileException("Couldn't initialize png info struct", __LINE__, __FILE__);
    }

    //custom read function
    png_set_read_fn(_readPngPtr,(png_voidp)_stream, userReadData);

    //read the header.
    //Set the amount signature bytes we've already read:
    png_set_sig_bytes(_readPngPtr, 8);

    //Now call png_read_info with our pngPtr as image handle, and infoPtr to receive the file info.
    png_read_info(_readPngPtr, _readInfoPtr);

    //If the data is contained in a palette, convert it to RGB
    if (png_get_color_type(_readPngPtr, _readInfoPtr) == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(_readPngPtr);
        _was_palette = true;
    }
}

void PngImage::initWrite()
{
    if(!_stream) {
        _stream = new fstream(_filename.c_str(), ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc);
    }

    //TODO : Error handling
    _writePngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)_errorPtr, userErrorHandler, userErrorHandler);

    if(!_writePngPtr) {
        throw ImageFileException("Couldn't initialize png write struct", __LINE__, __FILE__);
    }

    _writeInfoPtr = png_create_info_struct(_writePngPtr);
    if (!_writeInfoPtr)
    {
        png_destroy_write_struct(&_writePngPtr,
         (png_infopp)NULL);
        _writePngPtr = NULL;

        throw ImageFileException("Couldn't initialize png info struct", __LINE__, __FILE__);
    }

    //Set the custom write function using cpp standard streams
    png_set_write_fn(_writePngPtr, (png_voidp)_stream, userWriteData, NULL);

}
