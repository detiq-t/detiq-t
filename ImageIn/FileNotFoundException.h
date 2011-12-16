#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <iostream>
#include <sstream>
#include <exception>

namespace imagein
{
    class FileNotFoundException : public std::exception
    {
    public:
        FileNotFoundException( const char * Msg, int Line )
        {
            std::ostringstream oss;
            oss << "Erreur ligne " << Line << " : "
                << Msg;
            this->msg = oss.str();
        }

        virtual ~FileNotFoundException() throw()
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
