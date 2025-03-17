#ifndef __ILRD_RC_STRING_H__
#define __ILRD_COMPOSITE_H__

#include <string>



class RCString{
private:
    class StrWrapper;
    class ProxyChar;        
    StrWrapper *m_str;
    friend bool operator==(const RCString& a, const RCString& b);
    friend bool operator>(const RCString& a, const RCString& b);
    friend std::ostream& operator<<(std::ostream& os, const RCString& str);
public:
    RCString(std::string str = "unknown");
    ~RCString();
    RCString(const RCString& other);
    RCString& operator=(const RCString& other);
    const char& operator[](size_t index) const;         
    ProxyChar operator[](size_t index); 
    const std::string& ToCstr() const;
    int Length();
    
    
};

class RCString::StrWrapper{
public:

    StrWrapper(std::string str):m_str(str), m_refCntr(1){};
    void Decrement(){ --m_refCntr;}
    void Increment(){ ++m_refCntr;}
    int GetRefCntr(){return m_refCntr;}
    bool operator==(const StrWrapper& other){return m_str == other.m_str;}   
    const char& GetChar(size_t index) const{
        if(index >= m_str.size()){
            throw std::out_of_range("index out of range");  
    }
        return m_str.at(index);
    }
    const std::string& GetStr() const{return m_str;};

private:
    std::string m_str;
    int m_refCntr;
};

class RCString::ProxyChar{
public:
    inline ProxyChar(const char& chr): m_chr(const_cast<char&>(chr)){}
    inline char& operator=(char chr){return m_chr;}
    inline char operatorchar(){return m_chr;}
private: 
    char& m_chr; 
};


bool operator==(const RCString& a, const RCString& b);
bool operator!=(const RCString& a, const RCString& b);
bool operator<(const RCString& a, const RCString& b);
bool operator>(const RCString& a, const RCString& b);
std::ostream& operator<<(std::ostream& os, const RCString& str);

#endif //__ILRD_RC_STRING_H__