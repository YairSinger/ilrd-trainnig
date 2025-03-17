
#include <iostream>
#include "rcstring.hpp"


//test default constructor
void testDefaultConstructor()
{
    RCString s1;
    std::cout << s1 << std::endl;
}

//test copy constructor
void testCopyConstructor()
{
    RCString s1("hello");
    RCString s2(s1);
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}

//test assignment operator, copy on write
void testAssignmentOperator()
{
    RCString s1("hello");
    RCString s2;
    s2 = s1;
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
}

RCString CreateLocalRCString(const char* str)
{
    RCString s(str);
    std::cout << s << std::endl;
    std::cout << "exiting  first scope" << std::endl;
    return s;
}

//test local variable is freed after scope of one reference
void testLocalVarIsNotFreedAfterScopeOf1from2References()
{
    RCString s = CreateLocalRCString("hello");
    std::cout << s << std::endl;

}

//test copy on write
void testCopyOnWrite()
{
    RCString s1("hello");
    std::cout << s1 << std::endl;
    std::string str = "world";
    s1 = str; //implicit ctor call 
    std::cout << s1 << std::endl;
}

//test read char from RCString
void testReadChar()
{
    RCString s1("hello");
    char c = s1[0];
    std::cout << c << std::endl;
}

int main()
{
    // testDefaultConstructor();
    // testCopyConstructor();
    //testAssignmentOperator();
     //testLocalVarIsNotFreedAfterScopeOf1from2References();
     testCopyOnWrite();
    return 0;   
}
