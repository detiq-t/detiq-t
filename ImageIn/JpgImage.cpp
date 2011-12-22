#include "JpgImage.h"

using namespace imagein;
///*
// * JPEG ERROR HANDLING EXPLANATION
// *
// * The standard JPEG library exit the program when a fatal error occurs
// * That's not what we want, we would rather raise an exception,
// *  so we need to override the standard JPEG error routine.
// * The only way to do so, is by using low level old school C.
// * So we need to define a structure and a handler.
// * The jpegErrorManager structure is the same as jpeg_error_mgr
// *  but with an additionnal field : setjmp_buffer
// * The setjmp_buffer always store the address where we need to jump
// *  to continue the execution, see setjmp for more informations.
// * The jpegErrorExit function is the error handler.
// * We tell JPEG to call jpegErrorExit when a fatal error occurs
// *  and we give it a jpegErrorManager instead of a jpeg_error_mgr
// * When an error occurs, JPEG call jpegErrorExit and give it
// *  as a parameter a structure wich contains a pointer to the
// *  jpeg_error_mgr structure previously allocated.
// * But this pointer do not only point to a jpeg_error_mgr structure,
// * but also to a jpegErrorManager structure, so we just have to cast it
// * in order to get the setjmp_buffer wich contains the address where we need to jump.
// * It may looks like a makeshift job to a C++ developper but it is the official way.
// *
// */
//struct jpegErrorManager {
//    /* "public" fields */
//    struct jpeg_error_mgr pub;
//    /* for return to caller */
//    jmp_buf setjmp_buffer;
//};
//
//void jpegErrorExit (j_common_ptr cinfo)
//{
//    /* cinfo->err actually points to a jpegErrorManager struct */
//    my_error_mgr* myerr = (my_error_mgr*) cinfo->err;
//    /* note : *(cinfo->err) is now equivalent to myerr->pub */
//
//    /* output_message is a method to print an error message */
//    (* (cinfo->err->output_message) ) (cinfo);
//
//    /* Jump to the setjmp point */
//    longjmp(myerr->setjmp_buffer, 1);
//}
//
//void readFromJpeg(std::string filename) {
//    /* Contains the JPEG decompression parameters and results */
//    struct jpeg_decompress_struct cinfo;
//
//    /* Our private error handler structure (see explanation above) */
//    struct jpegErrorManager jerr;
//
//    /* We open the file to give a handler to the JPEG library */
//    FILE * infile;
//    if( (infile = fopen(filename, "rb")) == NULL ) {
//        fprintf(stderr, "can't open %s\n", filename);
//        return 0;
//    }
//
//    /* We set up the normal JPEG error routines, then override error_exit. */
//    cinfo.err = jpeg_std_error(&jerr.pub);
//    jerr.pub.error_exit = jpeagErrorExit;
//
//    /* Establish the setjmp return context for my_error_exit to use. */
//    if (setjmp(jerr.setjmp_buffer)) {
//        /* If we get here, the JPEG code has signaled an error. */
//        jpeg_destroy_decompress(&cinfo);
//        fclose(infile);
//        return 0;
//    }
//
//    /* Wwe initialize the JPEG decompression object. */
//    jpeg_create_decompress(&cinfo);
//    /* We specify data source */
//    jpeg_stdio_src(&cinfo, infile);
//
//    /* We read the JPEG header, the TRUE means we reject tables-only JPEG file */
//    jpeg_read_header(&cinfo, TRUE);
//
//    /* We start the decompression */
//    jpeg_start_decompress(&cinfo);
//
//    /* Output row buffer */
//    JSAMPARRAY buffer;
//    /* JSAMPLEs per row in output buffer */
//    int row_stride = cinfo.output_width * cinfo.output_components;
//
//    this->_width = cinfo.output_width;
//    this->_height = cinfo.output_height;
//    this->_nChannels = cinfo.output_components;
//    cinfo.
//
//    printf("%d %d", cinfo.output_width, cinfo.output_height);
//    system("pause");
//
//    /* Make a one-row-high sample array that will go away when done with image */
//    buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
//
//    /* We read the decompression results */
//    /* We use the JPEG state variable as a loop counter */
//    while (cinfo.output_scanline < cinfo.output_height) {
//        jpeg_read_scanlines(&cinfo, buffer, 1);
//        for(int i=0; i<this->_width; i++) {
//            for(int j=0; j<this->_nChannels; j++) {
//
//            }
//        }
//        //put_scanline_someplace(buffer[0], row_stride);
//    }
//
//  /* Step 7: Finish decompression */
//
//  (void) jpeg_finish_decompress(&cinfo);
//  /* We can ignore the return value since suspension is not possible
//   * with the stdio data source.
//   */
//
//  /* Step 8: Release JPEG decompression object */
//
//  /* This is an important step since it will release a good deal of memory. */
//  jpeg_destroy_decompress(&cinfo);
//
//  /* After finish_decompress, we can close the input file.
//   * Here we postpone it until after no more JPEG errors are possible,
//   * so as to simplify the setjmp error logic above.  (Actually, I don't
//   * think that jpeg_destroy can do an error exit, but why assume anything...)
//   */
//  fclose(infile);
//
//  /* At this point you may want to check to see whether any corrupt-data
//   * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
//   */
//
//  /* And we're done! */
//  return 1;
//}
unsigned int JpgImage::readHeight(){
    //TODO
    return 0;
}

unsigned int JpgImage::readWidth(){
    //TODO
    return 0;
}

unsigned int JpgImage::readNbChannels(){
    //TODO
    return 0;
}

unsigned int JpgImage::readDepth(){
    //TODO
    return 0;
}

char* JpgImage::readData(){
    //TODO
    return NULL;
}

void JpgImage::writeData(const char* const data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth){
    //TODO
}

