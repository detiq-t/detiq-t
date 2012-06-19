/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LOG_H_02022012
#define LOG_H_02022012

/* stl include */

#include <fstream>
#include <string>
#include <exception>
#include <map>
#include <iostream>

/**
* @file Log.h
* @brief The logs, in debugging, are very important. This Log class will help the developper in his task
* @author Thomas Letan
* @version 0.1
* @date 2012-02-15
*/

/**
* @brief This class provides to the developper a set of tools to follow his logs
* 
* It gives two ways for it : terminal view and file saves. Each log has an importance
* (LEVEL) and a tag (it helps to understand quickly what the subject of the log
*
* With the file, use cat file | grep TAG
*/
class Log
{
public:
  /**
  * @enum LEVEL
  * @brief Each log has a level of importance
  */
  enum LEVEL
  {
    VERBOSE, /*!< The application just explain what it's doing */
    INFO,    /*!< The application gives an information, such as the success of connection, etc. */
    WARNING, /*!< The application tells that something unexpected happened. */
    CRITICAL /*!< The application tells that something unexpected and wrong happened */
  };

  /**
  * @brief The configuration of the log entity
  *
  * @param act True if the developper want the log to run
  * @param term True if the developper want the log to be printed in the terminal, false if it is in the log file
  * @param minlevel The less important level wanted to be considered (ex : INFO imply that VERBOSE aren't printed
  */
  static void configure (bool act, bool term, int minlevel);

  /**
  * @brief Add a new VERBOSE log
  *
  * @param s The log
  * @param tag The tag of the log
  */
  static void verbose (std::string s, std::string tag = "APP");
  /**
  * @brief Add a new INFO log
  *
  * @param s The log
  * @param tag The tag of the log
  */
  static void info (std::string s, std::string tag = "APP");
  /**
  * @brief Add a new WARNING log
  *
  * @param s The log
  * @param tag The tag of the log
  */
  static void warning (std::string s, std::string tag = "APP");
  /**
  * @brief Add a new CRITICAL log
  *
  * @param s The log
  * @param tag The tag of the log
  */
  static void critical (std::string s, std::string tag = "APP");

protected:
  /**
  * @brief Generic function to add a new log
  *
  * @param l the level of the log
  * @param s the log
  * @param tag the tag of the log
  */
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
