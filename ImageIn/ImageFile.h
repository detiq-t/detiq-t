#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include <string>


namespace imagein
{
    class ImageFile
    {
        public:

            typedef enum {
                F_BMP,
                F_JPG,
                F_PNG,
                F_WEBP
            }Format;

            ImageFile(std::string filename) : _filename(filename) {}

            virtual unsigned int readHeight()=0;
            virtual unsigned int readWidth()=0;
            virtual unsigned int readNbChannels()=0;
            virtual unsigned int readDepth()=0;
            virtual char* readData()=0;

            virtual void writeData(char* data, unsigned int width, unsigned int height, unsigned int nChannels, unsigned int depth)=0;

        private:
            std::string _filename;
    };
}

#endif // IMAGEFILE_H
