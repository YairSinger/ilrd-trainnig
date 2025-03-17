#include <iostream>
#include <vector>
using namespace std;




int main() {
    
    std::vector<int> v = {1,5,8,3,7,4,22,4,-15,-2};
    for (auto &&i : v)
    {
        cout << i << endl;
    }
    auto sumTotal = [&]() 
    {
        int sum = 0; 
        for (auto &&i : v) sum += i;
        return sum;
    }();

    cout<< "sum of vector is : " << sumTotal << endl;
    // recive  one int from stdin to vector
    int input;
    cin >> input;
    v.push_back(input);
    cout<< "sum of vector is : " << sumTotal << endl;
    


    return 0;
}