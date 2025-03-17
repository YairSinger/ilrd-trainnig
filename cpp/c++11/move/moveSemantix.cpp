#include <iostream>
#include <vector>
#include <chrono>

// class Object {
// public:
//     Object() {
//         // Simulating some work done during object creation
//         data = new int[1000];
//     }

//     ~Object() {
//         delete[] data;
//     }

//     // Copy constructor
//     Object(const Object& other) {
//         data = new int[100];  // Simulate a deep copy
//         std::copy(other.data, other.data + 100, data);
//     }

//     // Move constructor
//     Object(Object&& other) noexcept {
//         data = other.data;
//         other.data = nullptr;  // Invalidate the moved-from object
//     }
//      void unchanged(Object&& other){
//         other.data[0] = -1;
//      }

// private:
//     int* data;
//     int x;

// };

// class StackWithoutMove {
// public:
//     void push(const Object& obj) {
//         stack.push_back(obj);
//     }

// private:
//     std::vector<Object> stack;
// };

// class StackWithMove {
// public:
//     void push(Object&& obj) {
//         stack.push_back(std::move(obj));  // Move the object into the stack
//     }

// private:
//     std::vector<Object> stack;
// };

// int main() {
//     StackWithoutMove stack;

//     auto start = std::chrono::high_resolution_clock::now();

//     // Create and push 1000 objects
//     for (int i = 0; i < 1000000; ++i) {
//         Object obj;
//         stack.push(obj);
//     }

//     auto end = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration = end - start;

//     std::cout << "Time without move: " << duration.count() << " seconds" << std::endl;

//      StackWithMove stack2;

//     auto start2 = std::chrono::high_resolution_clock::now();

//     // Create and push 1000 objects
//     for (int i = 0; i < 1000000; ++i) {
//         Object obj;
//         stack2.push(std::move(obj));  // Move the object to the stack
//     }

//     auto end2 = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> duration2 = end2 - start2;

//     std::cout << "Time with move: " << duration2.count() << " seconds" << std::endl;

//     return 0;
// }

class B{
    public:
    B(int x =0): x(x) {std::cout << "B ctor" << std::endl;}
    int x;
};

class A{
    
    public:
    A(int x =0, int y = 1): x(x), y(y) {}

    void  static swapMem(A&& a, A&& b){
        std::swap(a.x, b.x); std::swap(a.y, b.y);  // swapMem)
    }

        B x;
        B y;
   
};

void swap(int &&a, int &&b){
    int temp = a;
    a = b;
    b = temp;
    a

}

int main(int argc, char const *argv[])
{
//    A a(1,2);
//    A b(3,4);

//    A::swapMem(std::move(a),std::move(b));
//    std::cout << a.x.x << " " << a.y.x << std::endl;
//    std::cout << b.x.x << " " << b.y.x << std::endl;

    int a = 1;
    int b = 2;

    swap(static_cast<int&&>(a), static_cast<int&&>(b));
    std::cout << a << " " << b << std::endl;

    return 0;
}

