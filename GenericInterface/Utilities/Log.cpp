/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-T�tu, Florian Teyssier
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

#include "Log.h"

using namespace std;


int Log::_miniLevel (0);
ostream* Log::_stream (0);
bool Log::_active (false);
bool Log::_terminal (false);
map<Log::LEVEL, string> Log::_levels;
map<Log::LEVEL, string> Log::_levelColors;

void Log::configure (bool act, bool term, int minilevel)
{
  _active = act;
  _terminal = term;
  _miniLevel = minilevel;

  _levels[VERBOSE]  = "(verbose) ";
  _levels[INFO]     = "(info)    ";
  _levels[WARNING]  = "(warning) ";
  _levels[CRITICAL] = "(critical)";

  _stream = _terminal ? &cout : new ofstream(".log");

  #ifdef __linux__
  if (_terminal)
  {
    _levelColors[VERBOSE]  = "\033[0m";
    _levelColors[INFO]     = "\033[32m";
    _levelColors[WARNING]  = "\033[33m";
    _levelColors[CRITICAL] = "\033[31m";
  }
  else
  {
    _levelColors[VERBOSE]  = "";
    _levelColors[INFO]     = "";
    _levelColors[WARNING]  = "";
    _levelColors[CRITICAL] = "";
  }
  #else
  _levelColors[VERBOSE]  = "";
  _levelColors[INFO]     = "";
  _levelColors[WARNING]  = "";
  _levelColors[CRITICAL] = "";
  #endif

}


void Log::verbose (std::string s, std::string tag)
{
  if(_miniLevel <= VERBOSE)
    Log::write (VERBOSE, s, tag);
}

void Log::info (std::string s, std::string tag)
{
  if(_miniLevel <= INFO)
    Log::write (INFO, s, tag);
}

void Log::warning (std::string s, std::string tag)
{
  if(_miniLevel <= WARNING)
    Log::write (WARNING, s, tag);
}

void Log::critical (std::string s, std::string tag)
{
  if(_miniLevel <= CRITICAL)
    Log::write (CRITICAL, s, tag);
}

void Log::write (Log::LEVEL l, string s, string tag)
{
  if (_active)
  {
    (*_stream) << _levelColors[l] << _levels[l] << " " << tag << ": " << s << endl << _levelColors[VERBOSE];
  }
}
