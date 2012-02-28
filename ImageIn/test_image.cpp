#include <iostream>
#include <cmath>

#include "Image.h"

using namespace imagein;
using namespace std;

int main(int argc, char* argv[])
{
    /*
     * Test I/O jpg, bmp, png
     */
    
    //reference data
    int width = 512;
    int height = 255;
    int nbChannels = 3;
    unsigned char* dataRgb = new unsigned char[width * height * nbChannels];

    for(int j = 0 ; j < height ; ++j) {
        for(int i = 0 ; i < width ; ++i) { 
            unsigned char red = 255 - i;
            if(red < 0) red = 0;
            unsigned char green = 255 - abs(256-i);
            if(green < 0) green = 0;
            unsigned char blue = 255 - abs(512-i);
            if(blue < 0) blue = 0;
            
            dataRgb[j*width*nbChannels + i*nbChannels] = red;
            dataRgb[j*width*nbChannels + i*nbChannels + 1] = green;
            dataRgb[j*width*nbChannels + i*nbChannels + 2] = blue;
        }
    }

    Image in(width, height, nbChannels, dataRgb);

    in.save("test/ref_image.jpg");
    in.save("test/ref_image.jpeg");
    in.save("test/ref_image.png");
    exit(0);
    in.save("test/ref_image.bmp");


    //cout << "Testing ImageFile I/O functions..." << endl;
    
    ////Testing jpeg writing
    //nTest++;
    //Image jpgTest("test/temp/test_io_bmp.jpg");
    
    //Image::const_iterator b1 = in.begin(), b2 = jpgTest.begin(), e1 = in.end(), e2 = jpgTest.end();

    //if(
            //std::equal(b1, e1, b2) //Matrices are equals
         //&& (e2-b2 == e1-b1) //Matrices are same size
         //&& in.getWidth() == jpgTest.getWidth() //Class attributes are equals
         //&& in.getHeight() == jpgTest.getHeight()
         //&& in.getNbChannels() == jpgTest.getNbChannels()
      //) {
        //cout << "[OK]   jpg writing" << endl;
    //}
    //else {
        //cerr << "[FAIL] jpg writing" << endl;
        //nFail++;
    //}

    ////Testing png writing
    //nTest++;
    //Image pngTest("test/temp/test_io_bmp.png");
    
    //Image::const_iterator b1 = in.begin(), b2 = pngTest.begin(), e1 = in.end(), e2 = jpgTest.end();

    //if(
            //std::equal(b1, e1, b2) //Matrices are equals
         //&& (e2-b2 == e1-b1) //Matrices are same size
         //&& in.getWidth() == pngTest.getWidth() //Class attributes are equals
         //&& in.getHeight() == pngTest.getHeight()
         //&& in.getNbChannels() == pngTest.getNbChannels()
      //) {
        //cout << "[OK]   png writing" << endl;
    //}
    //else {
        //cerr << "[FAIL] png writing" << endl;
        //nFail++;
    //}
    
    ////Testing bmp writing
    //nTest++;
    //Image bmpTest("test/temp/test_io_bmp.bmp");
    
    //Image::const_iterator b1 = in.begin(), b2 = bmpTest.begin(), e1 = in.end(), e2 = jpgTest.end();

    //if(
            //std::equal(b1, e1, b2) //Matrices are equals
         //&& (e2-b2 == e1-b1) //Matrices are same size
         //&& in.getWidth() == bmpTest.getWidth() //Class attributes are equals
         //&& in.getHeight() == bmpTest.getHeight()
         //&& in.getNbChannels() == bmpTest.getNbChannels()
      //) {
        //cout << "[OK]   bmp writing" << endl;
    //}
    //else {
        //cerr << "[FAIL] bmp writing" << endl;
        //nFail++;
    }
