#ifndef SERVICEEXCEPTIONS_H_02022012
#define SERVICEEXCEPTIONS_H_02022012

#include <sstream>
#include <exception>


class ServiceConnectionException : public std::exception
{
  public:
    ServiceConnectionException(int src, int dst)
    {
      _src = src;
      _dst = dst;
    }

    virtual const char* what () const throw ()
    {
      std::ostringstream err;
      err << "the service " << _src << " fails to connect with the service " << _dst;

      return err.str ().c_str ();
    }
  private:
    int _src;
    int _dst;
};

#endif
