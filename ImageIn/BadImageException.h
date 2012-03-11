
#ifndef BADIMAGEEXCEPTION_H
#define BADIMAGEEXCEPTION_H

#include <iostream>
#include <sstream>
#include <exception>

namespace imagein
{
    //! This is the exception thrown when the image if of an unexpected format (incorrect number of channels, color space...)
    class BadImageException : public std::exception
    {
    public:
        BadImageException( const std::string& msg, int line, std::string file)
        {
            std::ostringstream oss;
            oss << "Exception raised line " << line << " in file " << file << " : "
                << msg;
            this->msg = oss.str();
        }

        virtual ~BadImageException() throw()
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

#endif // BADIMAGEEXCEPTION_H
