
#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

class MyString {
private:
    char* str;
public:
    MyString() : str(NULL) {
        cout << "MyString() is called" << endl;
    }
    
    MyString(const char* newStr) {
        cout << "MyString(const char*) is called" << endl;
        str = new char[strlen(newStr) + 1];
        strcpy(str, newStr);
    }
    MyString(const MyString& other) {
        cout << "MyString(const MyString&) is called" << endl;
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }

    MyString& operator=(const MyString& other) {
        cout << "operator=(const MyString&) is called" << endl;
        if (this != &other) {
            delete[] str;
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    MyString& operator+(const MyString& other) {
        cout << "operator+(const MyString&) is called" << endl;
        char* newStr = new char[strlen(str) + strlen(other.str) + 1];
        strcpy(newStr, str);
        strcat(newStr, other.str);
        delete[] str;
        str = newStr;
        return *this;
    }

    // MyString(MyString&& other) noexcept {
    //     cout << "MyString(MyString&&) is called" << endl;
    //     str = other.str;
    //     other.str = nullptr;
    // }

    // MyString& operator=(MyString&& other) noexcept {
    //     cout << "operator=(MyString&&) is called" << endl;
    //     if (this != &other) {
    //         delete[] str;
    //         str = other.str;
    //         other.str = nullptr;
    //     }
    //     return *this;
    // }

    ~MyString() {
        cout << "~MyString() is called" << endl;
        delete[] str;
    }

    void print() const {
        if (str) {
            cout << str << endl;
        } else {
            cout << "nullptr" << endl;
        }
    }

    void setString(const char* newStr) {
        delete[] str;
        str = new char[strlen(newStr) + 1];
        strcpy(str, newStr);
    }
};

void TestMoveCtorWhenAppendingTwoStrings() {
    MyString s1 = "hello";
    MyString s2 = "world";
    MyString s3 = s1 + s2;
    s3.print();
}

int main() {

//    MyString s1 = "hello";
//    MyString s2 = "world";

//    MyString s3 = s1 + s2;
   TestMoveCtorWhenAppendingTwoStrings();
    return 0;
}
