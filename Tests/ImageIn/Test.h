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

#ifndef TEST_H
#define TEST_H

class Test {
  public:
    
    virtual std::string info() = 0;
    Test(std::string name) : _name(name) {}

    std::string getName() { return _name; }

    virtual bool operator()() {
        std::string msg = "";
        bool initd = false;
        try {
            initd = init();
        }
        catch(const std::exception& e) { msg = e.what(); }
        catch(const std::exception* e) { msg = e->what(); }
        catch(const std::string& e) { msg = e; }
        catch(const std::string* e) { msg = *e; }
        catch(const char* e) { msg = e; }

        if(!initd) {
            std::cerr << "[init error";
            if(msg != "") std::cerr << " : " << msg;
            std::cerr << "]";
            return false;
        }
        
        msg = "";
        bool testd = false;
        try {
            testd = test();
        }
        catch(const std::exception& e) { msg = e.what(); }
        catch(const std::exception* e) { msg = e->what(); }
        catch(const std::string& e) { msg = e; }
        catch(const std::string* e) { msg = *e; }
        catch(const char* e) { msg = e; }

        if(!testd) {
            std::cerr << "[test failed";
            if(msg != "") std::cerr << " : " << msg;
            std::cerr << "]";
            return false;
        }

        
        msg = "";
        bool cleand = false;
        try {
            cleand = cleanup();
        }
        catch(const std::exception& e) { msg = e.what(); }
        catch(const std::exception* e) { msg = e->what(); }
        catch(const std::string& e) { msg = e; }
        catch(const std::string* e) { msg = *e; }
        catch(const char* e) { msg = e; }

        if(!cleand) {
            std::cerr << "[clean failed";
            if(msg != "") std::cerr << " : " << msg;
            std::cerr << "]";
            return false;
        }

        return true;
        
    }
  protected:
    virtual bool init() = 0;
    virtual bool test() = 0;
    virtual bool cleanup() = 0;
    std::string _name;
};


#endif //!TEST_H
