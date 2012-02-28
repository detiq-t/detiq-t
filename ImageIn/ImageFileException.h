#ifndef IMAGEFILEEXCEPTION_H
#define IMAGEFILEEXCEPTION_H

#include <iostream>
#include <sstream>
#include <exception>

namespace imagein
{
    //! This is the exception thrown by ImageFile and its subclasses when there is an error reading from or writing in a file.
    class ImageFileException : public std::exception
    {
    public:
        ImageFileException( const std::string& msg, int line, std::string file)
        {
            std::ostringstream oss;
            oss << "Exception raised line " << line << " in file " << file << " : "
                << msg;
            this->msg = oss.str();
        }

        virtual ~ImageFileException() throw()
        {

        }

        virtual const char * what() const throw()
        {
            return this->msg.c_str();
        }

    private:
        std::string msg;
    };
}

#endif // FILENOTFOUNDEXCEPTION_H
