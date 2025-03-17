#include <stddef.h>
#include <iostream>
#include <unordered_map>
long fib(size_t n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    return fib(n-1) + fib(n-2);
}
// long fib2(size_t n){
//     std::unordered_map<size_t, long> memo;
//     memo[0] = 0;
//     memo[1] = 1;
//     if(memo.find(n) != memo.end()) return memo[n];
//     memo[n] = 
//     fib2(n-1) + fib2(n-2);
//     return memo[n];
// }

long fib22(size_t n){
    std::unordered_map<size_t, long> memo;
    memo[0] = 0;
    memo[1] = 1;
    for(size_t i = 2; i <= n; i++){
        memo[i] = memo[i-1] + memo[i-2];
    }
    return memo[n];
}



long fib3(size_t n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    long temp1 = 0;
    long temp2 = 1;
    long res = 0;
    for(size_t i = 2; i <= n; i++){
        res = temp1 + temp2;
        temp1 = temp2;
        temp2 = res;
    }
    return res; 
}

int main(){
    size_t n = 45;
   double statrTime = clock();
    for(size_t i = 0; i < 1; i++){
        fib(n);
    }
    std::cout << "Naive Time: " << (clock() - statrTime)/ CLOCKS_PER_SEC << "[sec]" <<  std::endl;

    // statrTime = clock();
    // for(size_t i = 0; i < 1; i++){
    //     fib2(n);
    // }
    // std::cout << "recursive with Memo Time: " << (clock() - statrTime)/ CLOCKS_PER_SEC << "[sec]" <<  std::endl;


    statrTime = clock();
    for(size_t i = 0; i < 1; i++){
        fib22(n);
    }
    std::cout << "Memo Time: " << (clock() - statrTime)/ CLOCKS_PER_SEC << "[sec]" <<  std::endl;

    statrTime = clock();
    for(size_t i = 0; i < 1; i++){
        fib3(n);
    }
    std::cout << "Optimized Time: and space " << (clock() - statrTime)/ CLOCKS_PER_SEC << "[sec]" <<  std::endl;
    return 0;
}