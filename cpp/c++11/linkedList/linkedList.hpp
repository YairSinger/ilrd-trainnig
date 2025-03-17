#include "MyIterator.hpp"





template<class U> class Node 
{   
    public:
    Node():next(nullptr){};
    Node(U value):next(nullptr), value(value){};
    Node(U value, Node<U>* next):next(next), value(value){};
    Node(const Node& other):next(other.next), value(other.value){};
    Node& operator++(){ return *next;};
    friend std::ostream& operator<<(std::ostream& os,const Node<U>& node){os << node.value; return os;};
    ~Node(){ delete next; };

    const U& getValue() const { return value; }
    Node<U>* getNext() const { return next; }
    
    private:
    Node<U>* next;
    U value;

};

template <class T> class MyLinkedList {
    private:
    Node<T> *head;
    Node<T> *tail;
    unsigned int size;

    public:
    MyLinkedList ():head(nullptr), size(0){
        tail = new Node<T>();//sentinel
    }

    ~MyLinkedList()        
    {
        while(head){
            Node<T> *temp = head;
            head = head->getNext();
            delete temp;
        }
        delete tail;
    }
    void pushHead(T element){
        Node<T> *elm = new Node<T>(element, head);        
        head = elm;   
        size++;     
    }
    T popHead(){
        Node<T> *temp = head;
        if(size ==0)
        {
            throw std::out_of_range("Empty list");
        }
        head = head->next;

        T popedElement = temp->value;
        delete temp;
        return popedElement;        
    }

    unsigned int getSize()const {
        return size;
    }

    MyIterator<Node<T>> begin(){
        return MyIterator<Node<T>>(head);
    }

    MyIterator<Node<T>> end(){
        return MyIterator<Node<T>>(*tail);
    }

};