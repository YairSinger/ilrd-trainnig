#include <iostream>
#include <iostream>

//*********************** ex1 ************************
// // Primary template
// template <int N>
// struct Factorial {
//     static const int Value = N * Factorial<N - 1>::Value;
// };

// // Base case specialization for factorial(0)
// template <>
// struct Factorial<0> {
//     static const int Value = 1;
// };

// int main() {
//     const int result = Factorial<7>::Value;
//     std::cout << "Factorial of 7 is: " << result << std::endl;
//     return 0;
// }


//***************** ex2 ********************


// template <int T>
// struct Fibonacci {

//     static constexpr int Value = Fibonacci<T - 1>::Value + Fibonacci<T - 2>::Value;
// };

// template <>
// struct Fibonacci<0> {
//     static const int Value = 0;
// };

// template <>
// struct Fibonacci<1> {
//     static const int Value = 1;
// };

// int main() {
    
//     static_assert(21 == Fibonacci<8>::Value, "This one will pass");
//     return 0;
// }


//***************** ex3 ********************

// template<typename T>
// T Add(T val){
//     return val;
// }
// //recursive call to Add
// template<typename T, typename... Args>
// T Add(T val, Args...args){
//     return  val + Add(args...);
// }

// int main(){

//     auto sum = Add(1, 1l, 1.0f, 1.0); // should return 4
//     std::cout << sum << std::endl;
//     return 0;
// }
//***************** ex4 ********************
template<typename T, typename V>
struct IsSame{
   static const bool value = false;
};


template<typename T>
struct IsSame<T,T>{
   static const bool value = true;
};





int main(){
    static_assert(IsSame<int, int>::value, "This one will pass");
    static_assert(IsSame<double, double>::value, "This one won't");
    return 0;
}


#include <iostream>
#include <functional>

// Function to add two numbers
int add(int a, int b) {
    return a + b;
}

// Function to multiply three numbers
int multiply(int a, int b, int c) {
    return a * b * c;
}

int main() {
    // Binding first argument of add function to 5
    auto addFive = std::bind(add, 5, std::placeholders::_1);

    // Calling addFive with different second arguments
    std::cout << "addFive(3): " << addFive(3) << std::endl;  // Output: 5 + 3 = 8
    std::cout << "addFive(7): " << addFive(7) << std::endl;  // Output: 5 + 7 = 12

    // Binding second and third arguments of multiply function to 2 and 3 respectively
    auto multiplyTwoThree = std::bind(multiply, std::placeholders::_1, 2, 3);

    // Calling multiplyTwoThree with different first arguments
    std::cout << "multiplyTwoThree(4): " << multiplyTwoThree(4) << std::endl;  // Output: 4 * 2 * 3 = 24
    std::cout << "multiplyTwoThree(5): " << multiplyTwoThree(5) << std::endl;  // Output: 5 * 2 * 3 = 30

    return 0;
}
