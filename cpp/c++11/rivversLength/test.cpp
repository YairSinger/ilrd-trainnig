#include <iostream>
#include <vector>
#include <algorithm> // for std::sort
using namespace std;

// Include the function declarations
vector<int> riverSizes(vector<vector<int>> matrix);
int length(vector<vector<int>> matrix, int i, int j);

// Test the riverSizes function
void testRiverSizes() {
    vector<vector<int>> testMatrix1 = {
        {1, 0, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 0, 0, 0, 1}
    };
    vector<int> expected1 = {2, 1, 2, 1, 1};
    vector<int> result1 = riverSizes(testMatrix1);
    sort(result1.begin(), result1.end()); // Sort for comparison
    sort(expected1.begin(), expected1.end());
    if (result1 == expected1) {
        cout << "Test 1 passed!" << endl;
    } else {
        cout << "Test 1 failed. Expected: ";
        for (int size : expected1) cout << size << " ";
        cout << "Got: ";
        for (int size : result1) cout << size << " ";
        cout << endl;
    }

    vector<vector<int>> testMatrix2 = {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 1}
    };
    vector<int> expected2 = {5};
    vector<int> result2 = riverSizes(testMatrix2);
    if (result2 == expected2) {
        cout << "Test 2 passed!" << endl;
    } else {
        cout << "Test 2 failed. Expected: ";
        for (int size : expected2) cout << size << " ";
        cout << "Got: ";
        for (int size : result2) cout << size << " ";
        cout << endl;
    }

    vector<vector<int>> testMatrix3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    vector<int> expected3 = {};
    vector<int> result3 = riverSizes(testMatrix3);
    if (result3 == expected3) {
        cout << "Test 3 passed!" << endl;
    } else {
        cout << "Test 3 failed. Expected: Empty result. Got: ";
        for (int size : result3) cout << size << " ";
        cout << endl;
    }

    vector<vector<int>> testMatrix4 = {
        {1}
    };
    vector<int> expected4 = {1};
    vector<int> result4 = riverSizes(testMatrix4);
    if (result4 == expected4) {
        cout << "Test 4 passed!" << endl;
    } else {
        cout << "Test 4 failed. Expected: 1. Got: ";
        for (int size : result4) cout << size << " ";
        cout << endl;
    }
}

int main() {
    testRiverSizes();
    return 0;
}
