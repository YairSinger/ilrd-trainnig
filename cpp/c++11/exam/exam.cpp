#include <cstring>
#include <iostream>

class StringYS
{
    public:
    StringYS(const char* input = "") {
        m_buffer = new char[strlen(input) + 1];
        strcpy(m_buffer, input);
    }
    StringYS(const StringYS& other) {
        m_buffer = new char[strlen(other.m_buffer) + 1];
        strcpy(m_buffer, other.m_buffer);
    }

    StringYS& operator=(const StringYS& other) {
        if (this != &other) {
            delete[] m_buffer;
            m_buffer = new char[strlen(other.m_buffer) + 1];
            strcpy(m_buffer, other.m_buffer);
        }
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& os, const StringYS& str); 
  
    private:

    char* m_buffer;

}

std::ostream& operator<<(std::ostream& os, const String& str){
    return os << str.m_buffer << "\n \t string address is: "<< str.m_buffer;
}

