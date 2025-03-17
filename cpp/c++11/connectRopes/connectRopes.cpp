#include <iostream>
#include <queue>
#include <vector>

#include <algorithm>
#include <cassert>


long connectRopes(const std::vector<int>& ropes) {
 

    std::priority_queue<int, std::vector<int>, std::greater<int>> min_que(ropes.begin(), ropes.end());
    long sumOfJoins = 0;
    while (min_que.size() > 1)
    {
       int first = min_que.top();
       min_que.pop();
       int sec = min_que.top();
       min_que.pop();
       sumOfJoins += first;
       sumOfJoins += sec;
       std::cout << first << " + " << sec << std::endl;
    min_que.push(first + sec);

    }
    
  
   
    return sumOfJoins;
}
void testConnectRopes() {
    // Test Case 1: Example from the prompt
    std::vector<int> ropes1 = {4, 3, 2, 6};
    assert(connectRopes(ropes1) == 29);
    
    // Test Case 2: Already sorted input
    std::vector<int> ropes2 = {1, 2, 3, 4, 5};
    assert(connectRopes(ropes2) == 33);
    
    // Test Case 3: Single rope (no cost)
    std::vector<int> ropes3 = {10};
    assert(connectRopes(ropes3) == 0);
    
    // Test Case 4: Two ropes (simple sum)
    std::vector<int> ropes4 = {5, 10};
    assert(connectRopes(ropes4) == 15);
    
    // Test Case 5: Large numbers
    std::vector<int> ropes5 = {100, 200, 300, 400, 500};
    assert(connectRopes(ropes5) == 3300);

    std::cout << "All test cases passed!" << std::endl;
}

int main() {
    testConnectRopes();
    return 0;
}