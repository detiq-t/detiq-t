#ifndef OPENERROREXCEPTION_H
#define OPENERROREXCEPTION_H

#include <exception>

namespace imagein
{
    class OpenErrorException : public std::exception
    {
        public:
            OpenErrorException(std::string msg) : _msg(msg) {}

            ~OpenErrorException() throw() {};

            const char* what() const throw()
            {
                return _msg.c_str();
            }

        private:
            std::string _msg;
    };
}



#endif // OPENERROREXCEPTION_H
