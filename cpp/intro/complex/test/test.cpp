#include <chrono>
#include "complex.hpp"
using namespace std::chrono;


// Use auto keyword to avoid typing long
// type definitions to get the timepoint
// at this instant use function now()



int main(){
    Complex a(2.2,1);
     std::cout << "a.m_r " << a.getReal() <<"a.m_i "  << a.getImaginary() << std::endl;
    std::cout << a << std::endl;
    Complex b(3, 5);
    // Complex c = a + b;
    // std::cout << c << std::endl;
    // c = a + 3;
    // std::cout << c << std::endl;
    // c = 3 + a;
    // std::cout << c << std::endl;

    auto start = high_resolution_clock::now();
    for( int i = 0; i < 100000; ++i)
    {
       a += b; 
    std::cout << a << std::endl;
    }

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() << "by value func time " <<std::endl;


    return 0;

}
