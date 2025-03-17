

#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std; 

struct BadDog: public runtime_error 
{   
    BadDog(const string& s_ = "This is a bad dog"): runtime_error(s_) {} 
}; 

class X {
    public:
        X(){cout <<"X::ctor called"<< endl;}
        virtual ~X(){cout <<"X::dtor called"<< endl;}

};

void Fifi()
{ 
    throw BadDog("bad pup"); cerr << "Fifi() after throw" << endl; 
} 
void Foo() 

{ 
        X x1;     
     try
     {
        /* code */
        Fifi();     
        cerr << "Foo() after Fifi()" << endl; 
     }
     catch(const std::exception& e)
     {
        std::cerr << e.what() << '\n';
     }
     
} 

void Bar() 
{ 
    Foo(); 
    cerr << "Bar() after Foo()" << endl; 
} 
int main() {     
    try     
    {         
        Bar();     
    }     
    catch(bad_alloc&)     
    {         
        cerr << "Out of memory! exiting."; exit(2);     
    }     
    catch(BadDog& b)     
    {         
        cerr << "Bad dog exception: " << b.what(); exit(3);     
    }     
    catch( exception& r )
    {
        cerr << "unknown exception: " << r.what();
        exit(4);     
    }
    return 0; 
}