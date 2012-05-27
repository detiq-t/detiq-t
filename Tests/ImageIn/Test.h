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
