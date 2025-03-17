#include <iostream>
#include <cstring>

class String {
private:
    char* buffer;

public:
    // Constructor
    String(const char* input = "") {
        buffer = new char[strlen(input) + 1];
        strcpy(buffer, input);
    }

    // Copy constructor
    String(const String& other) {
        buffer = new char[strlen(other.buffer) + 1];
        strcpy(buffer, other.buffer);
    }

    // Assignment operator
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] buffer;
            buffer = new char[strlen(other.buffer) + 1];
            strcpy(buffer, other.buffer);
        }
        return *this;
    }

    // Destructor
    ~String() {
        delete[] buffer;
    }

    // Overloaded << operator for output
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        os << str.buffer;
        return os;
    }

    // Overloaded >> operator for input
    friend std::istream& operator>>(std::istream& is, String& str) {
        char temp[4096]; // assuming maximum input length is 4096 characters
        is >> temp;
        str = temp;
        return is;
    }
};

int main() {
    String str1 = "hello world";
    String str2(str1);
    str2 = str1;
    std::cout << str2 << std::endl;
    std::cin >> str1;
    std::cout << "You entered: " << str1 << std::endl;

    return 0;
}
