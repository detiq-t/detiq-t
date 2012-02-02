#ifndef INTERFACEEXCEPTIONS_H_02022012
#define INTERFACEEXCEPTIONS_H_02022012

#include <sstream>
#include <exception>

class BadIdException : public std::exception
{
  public:
    BadIdException (int id)
    {
      _id = id;
    }

    virtual const char* what () const throw ()
    {
      std::ostringstream err;
      err << "the id " << _id << " is already used";

      return err.str ().c_str ();
    }
  private:
    int _id;
};

#endif
