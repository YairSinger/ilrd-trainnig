#include <iostream>
#include "rcstring.hpp"

RCString::RCString(std::string str): m_str(new RCString::StrWrapper(str)){}
RCString :: ~RCString(){
    m_str->Decrement();

    if(0 == m_str->GetRefCntr()){
        delete(m_str);
    }

 }



 RCString::RCString(const RCString& other): m_str(other.m_str){
    m_str->Increment();
 }

RCString& RCString::operator=(const RCString& other){
    m_str->Decrement();
    if(m_str->GetRefCntr() == 0){
        delete(m_str);
        std::cout << "assignment operator called" << std::endl;
    } 

    m_str = other.m_str;
    m_str->Increment();     
    
    return *this;
} 

const char& RCString::operator[](size_t index) const{
    return m_str->GetChar(index);
}

RCString::ProxyChar RCString::operator[](size_t index){
    return ProxyChar(m_str->GetChar(index));
}


const std::string& RCString::ToCstr() const {
    return m_str->GetStr();}

int RCString::Length(){
    return m_str->GetStr().size();
}


bool operator==(const RCString& a, const RCString& b){
    return a.ToCstr() == b.ToCstr();
}

bool operator>(const RCString& a, const RCString& b){
    return a.ToCstr() > b.ToCstr();
}   


bool operator<(const RCString& a, const RCString& b){
    return !(b > a);
}

bool operator!=(const RCString& a, const RCString& b){
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const RCString& str){
    return os << str.ToCstr() << "\n \t string address is: "<< str.m_str;
}


