#include "PngImage.h"

#include "ImageFileException.h"

using namespace imagein;
using namespace std;

//TODO : error handling.

PngImage::PngImage(string filename)
 : ImageFile(filename), _readPngPtr(NULL), _writePngPtr(NULL), _stream(NULL), _was_palette(false)
{
    _stream = new fstream(filename.c_str(), ios_base::in | ios_base::binary);

    if(_stream->fail()) { //If the file isn't readable (probably doesn't exists)
        delete _stream;
        _stream = NULL;
    }
    else {
        //Allocate a buffer of 8 bytes, where we can put the file signature.
        png_byte pngsig[8];

        //Read the 8 bytes from the stream into the sig buffer.
        _stream->read((char*)pngsig, 8);

        //Check if the read worked...
        if (!_stream->good()) {
            throw ImageFileException("File "+filename+" is not a valid png file", __LINE__, __FILE__);
        }

        //Let LibPNG check the sig. If this function returns 0, everything is OK.
        if(png_sig_cmp(pngsig, 0, 8) != 0) {
            throw ImageFileException("File "+filename+" is not a valid png file", __LINE__, __FILE__);
        }

        _readPngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        if (!_readPngPtr) {
            throw ImageFileException("Couldn't initialize png read struct", __LINE__, __FILE__);
        }

        _infoPtr = png_create_info_struct(_readPngPtr);
        if (!_infoPtr) {
            png_destroy_read_struct(&_readPngPtr, (png_infopp)0, (png_infopp)0);
            throw ImageFileException("Couldn't initialize png info struct", __LINE__, __FILE__);
        }

        //custom read function
        png_set_read_fn(_readPngPtr,(png_voidp)_stream, userReadData);

        //read the header.
        //Set the amount signature bytes we've already read:
        png_set_sig_bytes(_readPngPtr, 8);

        //Now call png_read_info with our pngPtr as image handle, and infoPtr to receive the file info.
        png_read_info(_readPngPtr, _infoPtr);

        //If the data is contained in a palette, convert it to RGB
        if (png_get_color_type(_readPngPtr, _infoPtr) == PNG_COLOR_TYPE_PALETTE) {
            png_set_palette_to_rgb(_readPngPtr);
            _was_palette = true;
        }
    }
}

PngImage::~PngImage()
{
    delete _stream;

    if(_readPngPtr) {
        png_destroy_read_struct(&_readPngPtr, &_infoPtr,(png_infopp)0);
    }

    if(_writePngPtr) {
        png_destroy_write_struct(&_writePngPtr, (png_infopp)0);
    }
}

char* PngImage::readData()
{
    if(!_readPngPtr) {
        throw ImageFileException("File "+_filename+" is not a valid png file", __LINE__, __FILE__);
    }

    unsigned int w=readWidth(), h=readHeight(), c=readNbChannels(), d=readDepth();

    char* data = new char[ w * h * c * d/8]; //The actual array that will contain the data
    png_bytep* rowPtrs = new png_bytep[h];
    unsigned int rowSize = w*c*d/8;

    for (size_t i = 0; i < h; ++i) {
        rowPtrs[i] = (png_bytep)data + i*rowSize;
    }
    //now rowPtrs is an array of pointers, pointing on the beginning of each row

    //we can read the image.
    png_read_image(_readPngPtr, rowPtrs);

    delete[] rowPtrs;

    return data;
}

void PngImage::writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)
{
    _writePngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)NULL, NULL, NULL);

    _stream = new fstream(_filename.c_str(), ios_base::out | ios_base::binary);

    if(!_writePngPtr) {
        throw ImageFileException("Couldn't initialize png write struct", __LINE__, __FILE__);
    }

    _infoPtr = png_create_info_struct(_writePngPtr);  //TODO : what if there is already an info ptr ?
    if (!_infoPtr)
    {
        png_destroy_write_struct(&_writePngPtr,
         (png_infopp)NULL);
        _writePngPtr = NULL;

        throw ImageFileException("Couldn't initialize png info struct", __LINE__, __FILE__);
    }

    //Set the custom write function using cpp standard streams
    png_set_write_fn(_writePngPtr, (png_voidp)_stream, userWriteData, NULL);

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
    png_set_IHDR(_writePngPtr, _infoPtr, width, height,
       depth, colorType, PNG_INTERLACE_NONE,
       PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    //write file header
    png_write_info(_writePngPtr, _infoPtr);

    //preparing data
    png_bytep* rowPtrs = new png_bytep[height];
    unsigned int rowSize = width*nChannels*depth/8;

    for (size_t i = 0; i < height; ++i) {
        rowPtrs[i] = (png_bytep)data + i*rowSize;
    }
    //now rowPtrs is an array of pointers, pointing on the beginning of each row

    //we can write the data
    png_write_image(_writePngPtr, rowPtrs);

    //then the end of the file.
    png_write_end(_writePngPtr, _infoPtr);

    delete[] rowPtrs;
}