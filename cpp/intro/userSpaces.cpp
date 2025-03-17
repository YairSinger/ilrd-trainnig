#include <iostream> //cout

namespace useless
{ 
unsigned int g_wasteful[400];
extern int g_notthere;
void Foo() {
     std::cout << "Foo of useless" << std::endl;
};
void Foer(){}

inline namespace wasteoftyme
{
void Foo() {
    std::cout << "Foo of wasteoftyme" << std::endl;
};

void Foer(){}
}//namespace wasteoftyme
}//namespace useless

namespace stupid
{
void Foo() {
     std::cout << "Foo of stupid" << std::endl;
}
void Bar() {}
void DoNothing(unsigned int) {
    std::cout << "DoNothing of stupid" << std::endl;
}
}//namespace stupid

namespace useless
{
void DoNothing(int) {
     std::cout << "DoNothing of useless" << std::endl;
}

}//namespace useless


void DoStuff()
{
using namespace useless;
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo() {
     std::cout << "Foo of global" << std::endl;
}


namespace comeon = useless::wasteoftyme;

using namespace stupid;
void DoMoreStuff()
{
    comeon::Foo();
    //Foo(); //try uncommenting this line, solve the error
    Bar(); //why doesn't this line create an error?
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
void DoUselessStuff()
{
    DoNothing(g_wasteful[3] + 1);
}
}//namespace useless

int main(){
    useless::Foer();
    return 0;
}