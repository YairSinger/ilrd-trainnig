#include <ostream>

template<class T> 
class MyIterator{//singel value container iterator

    public:
        explicit MyIterator(T* value):m_value(value){ return *this;}
        explicit MyIterator(T& value):m_value(&value){ return *this;}
        explicit MyIterator(const MyIterator& other):m_value(other.m_value){ return *this;}
        T& current(){return m_value;}
        T& operator*(){return m_value->value;}
        T* operator->(){return m_value;}
        MyIterator& operator++(){m_value = m_value->next; return *this;}
        bool operator!=(const MyIterator& other){return m_value != other.m_value;}
        bool operator==(const MyIterator& other){return m_value == other.m_value;}
        friend std::ostream& operator<<(std::ostream& os, MyIterator<T>& it){os << it.m_value.value; return os;}
        T& next(){ T& value = m_value++; return value;}

        
       
        
    private:
       T* m_value;    

};

