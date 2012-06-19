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

#ifndef TESTER_H
#define TESTER_H

#include "Test.h"

class Tester {
  public:
    Tester(std::string name) : _name(name) {}

    
    virtual void init()=0;
    virtual void clean()=0;

    unsigned int operator()() {
        
        init();
        
        unsigned int error = 0;
        std::cout << "Testing " << _name << std::endl;
        for(std::vector<Test*>::iterator it = _tests.begin(); it < _tests.end(); ++it) {
            std::cout << "\t" << (*it)->getName() << "..." << std::flush;
            bool success = (**it)();
            if(success) {
                std::cout << "Success";
            }
            else {
                std::cout << "Failed";
                ++error;
            }
            std::string info = (*it)->info();
            if(info.size()>0) {
                std::cout << " (" << info  << ")";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        deleteTests(); 
        clean();
        
        return error;
    }
  protected:
    void addTest(Test* test) { _tests.push_back(test); }
    void deleteTests() {
        for(std::vector<Test*>::iterator it = _tests.begin(); it < _tests.end(); ++it) {
            delete *it;
        }
        _tests.clear();
    }
    std::vector<Test*> _tests;
    std::string _name;
};


#endif //!TESTER_H
