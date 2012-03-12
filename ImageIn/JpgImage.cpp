#include "JpgImage.h"

using namespace imagein;

extern "C" {
#include <jpeglib.h>
}
#include <csetjmp>
#include <cstdio>
#include <cstdlib>

#include "mystdint.h"

/*
 * JPEG ERROR HANDLING EXPLANATION
 *
 * The standard JPEG library exit the program when a fatal error occurs
 * That's not what we want, we would rather raise an exception,
 *  so we need to override the standard JPEG error routine.
 * The only way to do so, is by using low level old school C.
 * So we need to define a structure and a handler.
 * The jpegErrorManager structure is the same as jpeg_error_mgr
 *  but with an additionnal field : setjmp_buffer
 * The setjmp_buffer always store the address where we need to jump
 *  to continue the execution, see setjmp for more informations.
 * The jpegErrorExit function is the error handler.
 * We tell JPEG to call jpegErrorExit when a fatal error occurs
 *  and we give it a jpegErrorManager instead of a jpeg_error_mgr
 * When an error occurs, JPEG call jpegErrorExit and give it
 *  as a parameter a structure wich contains a pointer to the
 *  jpeg_error_mgr structure previously allocated.
 * But this pointer do not only point to a jpeg_error_mgr structure,
 * but also to a jpegErrorManager structure, so we just have to cast it
 * in order to get the setjmp_buffer wich contains the address where we need to jump.
 * It may looks like a makeshift job to a C++ developper but it is the official way.
 *
 */

struct jpegErrorManager {
    /* "public" fields */
    struct jpeg_error_mgr pub;
    /* for return to caller */
    jmp_buf setjmp_buffer;
};

void jpegErrorExit (j_common_ptr cinfo)
{
    /* cinfo->err actually points to a jpegErrorManager struct */
    jpegErrorManager* myerr = (jpegErrorManager*) cinfo->err;
    /* note : *(cinfo->err) is now equivalent to myerr->pub */

    /* output_message is a method to print an error message */
    (* (cinfo->err->output_message) ) (cinfo);

    /* Jump to the setjmp point */
    longjmp(myerr->setjmp_buffer, 1);
}


unsigned int JpgImage::readHeight(){
    struct jpeg_decompress_struct cinfo;
    FILE* fileHandler;
    /* We open the file to give a handler to the JPEG library */
    if( (fileHandler = fopen(this->_filename.c_str(), "rb")) == NULL ) {
        throw ImageFileException("Cannot open jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    /* We set up the normal JPEG error routines, then override error_exit. */
    jpegErrorManager jerr;
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpegErrorExit;
    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jerr.setjmp_buffer)) {
        /* If we get here, the JPEG code has signaled an error. */
        jpeg_destroy_decompress(&cinfo);
        fclose(fileHandler);
        throw ImageFileException("Error while decompressing jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    /* We initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);
    /* We specify data source */
    jpeg_stdio_src(&cinfo, fileHandler);
    /* We read the JPEG header, the TRUE means we reject tables-only JPEG file */
    jpeg_read_header(&cinfo, TRUE);
    /* We store the height of the image */
    unsigned int height = cinfo.image_height;
    /* Release JPEG decompression object
     * This is an important step since it will release a good deal of memory.
     */
    jpeg_destroy_decompress(&cinfo);
    /* After finish_decompress, we can close the input file.
     * Here we postpone it until after no more JPEG errors are possible,
     * so as to simplify the setjmp error logic above.  (Actually, I don't
     * think that jpeg_destroy can do an error exit, but why assume anything...)
     */
    fclose(fileHandler);
    return height;
}

unsigned int JpgImage::readWidth(){
    struct jpeg_decompress_struct cinfo;
    FILE* fileHandler;
    /* We open the file to give a handler to the JPEG library */
    if( (fileHandler = fopen(this->_filename.c_str(), "rb")) == NULL ) {
        throw ImageFileException("Cannot open jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    /* We set up the normal JPEG error routines, then override error_exit. */
    jpegErrorManager jerr;
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpegErrorExit;
    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jerr.setjmp_buffer)) {
        /* If we get here, the JPEG code has signaled an error. */
        jpeg_destroy_decompress(&cinfo);
        fclose(fileHandler);
        throw ImageFileException("Error while decompressing jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    /* We initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);
    /* We specify data source */
    jpeg_stdio_src(&cinfo, fileHandler);
    /* We read the JPEG header, the TRUE means we reject tables-only JPEG file */
    jpeg_read_header(&cinfo, TRUE);

    /* We store the height of the image */
    unsigned int width = cinfo.image_width;
    /* Release JPEG decompression object
     * This is an important step since it will release a good deal of memory.
     */
    jpeg_destroy_decompress(&cinfo);
    /* After finish_decompress, we can close the input file.
     * Here we postpone it until after no more JPEG errors are possible,
     * so as to simplify the setjmp error logic above.  (Actually, I don't
     * think that jpeg_destroy can do an error exit, but why assume anything...)
     */
    fclose(fileHandler);
    return width;
}

unsigned int JpgImage::readNbChannels(){
    struct jpeg_decompress_struct cinfo;
    FILE* fileHandler;
    /* We open the file to give a handler to the JPEG library */
    if( (fileHandler = fopen(this->_filename.c_str(), "rb")) == NULL ) {
        throw ImageFileException("Cannot open jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    /* We set up the normal JPEG error routines, then override error_exit. */
    jpegErrorManager jerr;
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpegErrorExit;
    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jerr.setjmp_buffer)) {
        /* If we get here, the JPEG code has signaled an error. */
        jpeg_destroy_decompress(&cinfo);
        fclose(fileHandler);
        throw ImageFileException("Error while decompressing jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    /* We initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);
    /* We specify data source */
    jpeg_stdio_src(&cinfo, fileHandler);
    /* We read the JPEG header, the TRUE means we reject tables-only JPEG file */
    jpeg_read_header(&cinfo, TRUE);
    /* We store the height of the image */
    unsigned int components = cinfo.num_components;
    /* Release JPEG decompression object
     * This is an important step since it will release a good deal of memory.
     */
    jpeg_destroy_decompress(&cinfo);
    /* After finish_decompress, we can close the input file.
     * Here we postpone it until after no more JPEG errors are possible,
     * so as to simplify the setjmp error logic above.  (Actually, I don't
     * think that jpeg_destroy can do an error exit, but why assume anything...)
     */
    fclose(fileHandler);
    return components;
}

unsigned int JpgImage::readDepth(){
    return sizeof(JSAMPLE);
}

void* JpgImage::readData(){
    struct jpeg_decompress_struct cinfo;
    FILE* fileHandler;
    /* We open the file to give a handler to the JPEG library */
    if( (fileHandler = fopen(this->_filename.c_str(), "rb")) == NULL ) {
        throw ImageFileException("Cannot open jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    /* We set up the normal JPEG error routines, then override error_exit. */
    jpegErrorManager jerr;
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpegErrorExit;
    /* Establish the setjmp return context for my_error_exit to use. */
    if (setjmp(jerr.setjmp_buffer)) {
        /* If we get here, the JPEG code has signaled an error. */
        jpeg_destroy_decompress(&cinfo);
        fclose(fileHandler);
        throw ImageFileException("Error while decompressing jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    /* We initialize the JPEG decompression object. */
    jpeg_create_decompress(&cinfo);
    /* We specify data source */
    jpeg_stdio_src(&cinfo, fileHandler);
    /* We read the JPEG header, the TRUE means we reject tables-only JPEG file */
    jpeg_read_header(&cinfo, TRUE);

    /* We start the decompression */
    jpeg_start_decompress(&cinfo);

    unsigned int width = cinfo.output_width;
    unsigned int height = cinfo.output_height;
    unsigned int nChannels = cinfo.output_components;
    unsigned int depth = sizeof(JSAMPLE)*8;
    unsigned int rowSize = width*nChannels*(sizeof(JSAMPLE)/sizeof(uint8_t));

    uint8_t* data = new uint8_t[height*rowSize];

    //int row_stride = cinfo->output_width * cinfo->output_components;
    //JSAMPARRAY buffer = (*cinfo->mem->alloc_sarray) ((j_common_ptr) cinfo, JPOOL_IMAGE, row_stride, 1);


    /* We read the decompression results */
    //for (unsigned int i=0; i < 1; i++) {
    while(cinfo.output_scanline < cinfo.output_height) {
        uint8_t* pos = &data[cinfo.output_scanline*rowSize];
        jpeg_read_scanlines(&cinfo, &pos, 1);
    }

    jpeg_finish_decompress(&cinfo);
    /* We can ignore the return value since suspension is not possible
     * with the stdio data source.
     */

    /* Release JPEG decompression object
     * This is an important step since it will release a good deal of memory.
     */
    jpeg_destroy_decompress(&cinfo);
    /* After finish_decompress, we can close the input file.
     * Here we postpone it until after no more JPEG errors are possible,
     * so as to simplify the setjmp error logic above.  (Actually, I don't
     * think that jpeg_destroy can do an error exit, but why assume anything...)
     */
    fclose(fileHandler);

    /* At this point you may want to check to see whether any corrupt-data
     * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
     */

    /* And we're done! */
    return data;
}

void JpgImage::writeData(const void* const data_, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth){

	const uint8_t* const data = reinterpret_cast<const uint8_t* const>(data_);
	
    /* This struct contains the JPEG compression parameters and pointers to
    * working space (which is allocated as needed by the JPEG library).
    * It is possible to have several such structures, representing multiple
    * compression/decompression processes, in existence at once.  We refer
    * to any one struct (and its associated working data) as a "JPEG object".
    */
    struct jpeg_compress_struct cinfo;
    /* This struct represents a JPEG error handler.  It is declared separately
    * because applications often want to supply a specialized error handler
    * (see the second half of this file for an example).  But here we just
    * take the easy way out and use the standard error handler, which will
    * print a message on stderr and call exit() if compression fails.
    * Note that this struct must live as long as the main JPEG parameter
    * struct, to avoid dangling-pointer problems.
    */
    struct jpeg_error_mgr jerr;
    /* More stuff */
    FILE * outfile;		/* target file */
    JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
    uintptr_t row_stride;		/* physical row width in image buffer */

    /* Step 1: allocate and initialize JPEG compression object */

    /* We have to set up the error handler first, in case the initialization
    * step fails.  (Unlikely, but it could happen if you are out of memory.)
    * This routine fills in the contents of struct jerr, and returns jerr's
    * address which we place into the link field in cinfo.
    */
    cinfo.err = jpeg_std_error(&jerr);
    /* Now we can initialize the JPEG compression object. */
    jpeg_create_compress(&cinfo);

    /* Step 2: specify data destination (eg, a file) */
    /* Note: steps 2 and 3 can be done in either order. */

    /* Here we use the library-supplied code to send compressed data to a
    * stdio stream.  You can also write your own code to do something else.
    * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
    * requires it in order to write binary files.
    */
    if ((outfile = fopen(this->_filename.c_str(), "wb")) == NULL) {
        throw ImageFileException("Cannot open jpeg file "+this->_filename, __LINE__, __FILE__);
    }
    jpeg_stdio_dest(&cinfo, outfile);

    /* Step 3: set parameters for compression */

    /* First we supply a description of the input image.
    * Four fields of the cinfo struct must be filled in:
    */
    cinfo.image_width = width; 	/* image width and height, in pixels */
    cinfo.image_height = height;
    cinfo.input_components = nChannels;		/* # of color components per pixel */

    /* colorspace of input image */
    switch(nChannels) {
        case 1:
            cinfo.in_color_space = JCS_GRAYSCALE;
            break;
        case 3:
            cinfo.in_color_space = JCS_RGB;
            break;
        case 4:
            cinfo.in_color_space = JCS_CMYK;
            break;
        default:
            throw ImageFileException("Unexpected number of channels for jpeg file", __LINE__, __FILE__);
    }

    /* Now use the library's routine to set default compression parameters.
    * (You must set at least cinfo.in_color_space before calling this,
    * since the defaults depend on the source color space.)
    */
    jpeg_set_defaults(&cinfo);
    /* Now you can set any non-default parameters you wish to.
    * Here we just illustrate the use of quality (quantization table) scaling:
    */
    jpeg_set_quality(&cinfo, 100, TRUE /* limit to baseline-JPEG values */);

    /* Step 4: Start compressor */

    /* TRUE ensures that we will write a complete interchange-JPEG file.
    * Pass TRUE unless you are very sure of what you're doing.
    */
    jpeg_start_compress(&cinfo, TRUE);

    /* Step 5: while (scan lines remain to be written) */
    /*           jpeg_write_scanlines(...); */

    /* Here we use the library's state variable cinfo.next_scanline as the
    * loop counter, so that we don't have to keep track ourselves.
    * To keep things simple, we pass one scanline per call; you can pass
    * more if you wish, though.
    */
    row_stride = width * nChannels;	/* JSAMPLEs per row in image_buffer */
	/* if the depth of the image in too large for JPEG, we use the offset to take the most significant Byte */
	uintptr_t offset = depth > 8 ? depth/8-1 : 0;

    while (cinfo.next_scanline < cinfo.image_height) {
        /* jpeg_write_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could pass
         * more than one scanline at a time if that's more convenient.
         */
        row_pointer[0] = (uint8_t*)& data[cinfo.next_scanline * row_stride + offset];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    /* Step 6: Finish compression */

    jpeg_finish_compress(&cinfo);
    /* After finish_compress, we can close the output file. */
    fclose(outfile);

    /* Step 7: release JPEG compression object */

    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_compress(&cinfo);

    /* And we're done! */
}
