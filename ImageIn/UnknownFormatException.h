#ifndef UNKNOWNFORMATEXCEPTION_H
#define UNKNOWNFORMATEXCEPTION_H

#include <iostream>
#include <sstream>
#include <exception>

namespace imagein
{
    class UnknownFormatException : public std::exception
    {
    public:
        UnknownFormatException(int line, std::string file)
        {
            std::ostringstream oss;
            oss << "Exception raised line " << line << " in file " << file;
            this->msg = oss.str();
        }

        virtual ~UnknownFormatException() throw()
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
