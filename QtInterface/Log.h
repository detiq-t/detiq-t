#ifndef LOG_H_02022012
#define LOG_H_02022012

#include <fstream>
#include <string>
#include <exception>
#include <map>
#include <iostream>

class UnknownLevelLog : public std::exception
{
  virtual const char* what () const throw()
  {
    return "Unknown log level asked";
  }
};

class Log
{
public:
  enum LEVEL
  {
    VERBOSE,
    INFO,
    WARNING,
    CRITICAL
  };

  static void configure (bool act, bool term, int minlevel);

  static void verbose (std::string s, std::string tag = "APP");
  static void info (std::string s, std::string tag = "APP");
  static void warning (std::string s, std::string tag = "APP");
  static void critical (std::string s, std::string tag = "APP");

  static void write (LEVEL l, std::string s, std::string tag) /*throw (UnknwonLevelLog)*/;

private:

  static int _miniLevel;
  static std::ostream* _stream;
  static bool _active;
  static bool _terminal;
  static std::map<LEVEL, std::string> _levels;
  static std::map<LEVEL, std::string> _levelColors;
};

#endif
