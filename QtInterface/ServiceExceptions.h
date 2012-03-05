#ifndef SERVICEEXCEPTIONS_H_02022012
#define SERVICEEXCEPTIONS_H_02022012

#include <sstream>
#include <exception>


namespace genericinterface
{
  /**
  * @brief One task of the Services is to connect themself,
  * with their connect() methods. If the connection is impossible,
  * the service throw a ServiceConnectionException.
  */
  class ServiceConnectionException : public std::exception
  {
    public:
      /**
      * @brief The constructor of a ServiceConnectionException
      *
      * @param src The id of the service which asks a connection
      * @param dst The id of the target service
      */
      ServiceConnectionException(int src, int dst)
      {
        _src = src;
        _dst = dst;
      }

      virtual const char* what () const throw ()
      {
        std::ostringstream err;
        err << "the service " << _src << " fails to connect with the service " << _dst;
        err << ", check the ids";

        return err.str ().c_str ();
      }
    private:
      int _src; /*!< The id of the service which asks a connection */
      int _dst; /*!< The id of the target service */
  };
}

#endif
