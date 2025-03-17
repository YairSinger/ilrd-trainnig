#include <iostream>
#include <vector>

struct UniformInitTest
{
    int x;
    int y[3];
    

};

  struct X
    {
        explicit X(int a, int b, int c): m_arr{a,b,c}{} // explicit constructor

        int m_arr[3];
    private:
    };

std::vector<int> yyy = {1,2,3};
auto xxx = std::vector<int>{1,2,3};
 auto add(int a, int b) -> decltype(a == b) { return a == b; } 

int main(){

    // int x = 4;
    // UniformInitTest  obj = {5,{1,2,3}};
    // int arr[3] = {5};

    // std::cout << arr[0] << std::endl;
    // std::cout << arr[1] << std::endl;
    // std::cout << arr[2] << std::endl;

     //::vector<int> v1(6); std::vector<int> v2 = {6,5};
//     std::cout << "v1 definined as: v1(6)" << std::endl;

//     for (auto &&i : v1)
//     {
//         std::cout << i;
//     }
//     std::cout << std::endl;
    
//      std::cout << "v2 definined as: v2 = {6,5}" << std::endl;

//    for (auto &&i : v2)
//     {
//         std::cout << i;
//     }
//     std::cout << std::endl;

    // X xObj(1,2,3);
    // for (size_t i = 0; i < 3; i++)
    // {
    //     std::cout << xObj.m_arr[i] << std::endl;
    // }

    // int arr[] = {1,2,3};
    // for (size_t i = 0; i < 3; i++)
    // {
    //     std::cout << arr[i] << std::endl;
    // }
        // yyy.pop_back();
        // xxx.pop_back();
   
   
    int x = 10, y = 10; 
    auto result = add(x, y); 
    std::cout << "Result: " << result  <<std::endl; // Output: Result: 15 
    

    return 0;
}