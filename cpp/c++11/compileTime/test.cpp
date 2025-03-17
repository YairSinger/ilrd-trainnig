#include <iostream>

class MyClass {
private:
    mutable int cachedValue; // Mutable member variable

public:
    MyClass() : cachedValue(0) {}

    // Const member function that modifies the mutable member variable
    int getValue() const {
        // Update the cached value if necessary
        if (cachedValue == 0) {
            // Some expensive computation to calculate the value
            cachedValue = calculateValue();
        }
        return cachedValue;
    }
    

    // Non-const member function
    void setValue(int value) {
        cachedValue = value;
    }

private:
    int calculateValue() const {
        // Simulated expensive computation
        return 42;
    }
};



   int main()
    {
        
        constexpr int a = std::cin.get();
        const_cast<int&>(a) = 4;

        
        std::cout << a << '\n';

        return 0;
    }

       #include <array>

    int main()
    {
       const size_t size = 10;

        std::array<int, size / 2> arr;

        return 0;
    }


  #include <array>

  constexpr size_t Half(size_t n) 
    {
        return n / 2;
    }

    int main()
    {
        std::array<int, Half(10)> arr;

        return 0;
    }