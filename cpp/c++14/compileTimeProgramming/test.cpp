// constexpr int factorial(int n) {
//     if (n <= 1) {
//         return 1;
//     } else {
//         return n * factorial(n - 1); // Recursive call
//     }
// }

// int main() {
//     constexpr int n = 5;
//     constexpr int result = factorial(n); // result is deduced at compile-time
//     static_assert(result == 120, "Incorrect factorial calculation");
//     return 0;
// }

#include <iostream>
#include <vector>
#include <shared_mutex>
#include <thread>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
      std::shared_timed_mutex mutex_;
    std::shared_lock<std::shared_timed_mutex> lock(mutex_);

    // Using std::cbegin to obtain a constant iterator to the beginning of vec
    auto it = std::begin(vec);

    // Attempting to modify the element pointed to by it will result in a compilation error
   int* ptr = &* it + 1;
    *it = 10; // Error: assignment of read-only location
    

   for (auto &&i : vec)
   {
    std::cout << i;
   }

   std::cout << *ptr << std::endl;
   

    return 0;
}
