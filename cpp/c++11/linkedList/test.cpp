#include <iostream>
#include <stdexcept>

template<typename T>
class Node
{
    T data;
    Node<T>* next;
    Node(T data): data(data), next(nullptr) {}
};


template<class U>
class SllIterator{
private:
    Node<u>* current;
public:
    SllIterator(Node<U>* node): current(node){}
    U& operator*(){return current->data;}
    U* operator->={return current->data;}
    SllIterator& operator++(){//postfix increasment
        current = current->next;
        return *this;
    }
    SllIterator operator++(int){//prefix increasment
        SllIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const SllIterator& other) const{
        return current == other.current;
    }

    bool operator!=(const SllIterator& other) const{
        return !(current == other.current);
    }

};

template<class Z>
class LinkedList{
private:
    Node<Z>*head;
    Node<Z>*tail;
    unsigned int size;
public:
    LinkedList():(head(nullptr),tail(nullptr),size(0)){}
    LinkeList(const LinkedList<Z>& other){
        Node<Z>* current = other.head;
        while(current){
            pushBack(current->data);
            current = current->next;
        }    
    }
    void pushBack(const Z& value){
        Node<Z>* newNode = new Node<Z>(value);
        if(!tail){
            head = tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }
    void pushfront(const Z& value){
        Node<Z>*newNode = new Node<Z>(value);
        newNode->next = head;
        head = newNode;
        ++size;
    }
    Z popBack(){
        if(!tail){
            throw std::out_of_range("List is empty");
        }
        Node<Z>* temp = tail;
        tail = tail->next;
        Z popedElement = temp->data;
        delete temp;
        --size;
        return popedElement;       
    }

    Z popFront(){
        if(!head){
            throw std::out_of_range("List is empty");
        }
        Node<Z>* temp = head;
        head = head->next;
        Z popedElement = temp->data;
        delete temp;
        --size;
        return popedElement;       
    }

    void clear(){
        while (head)
        {
            popFront();          
        }
        
    }

    unsigned int getSize(){
        return size;
    }

    const Z& peak(){
        if(!head){
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    SllIterator<Node<Z>> begin(){return SllIterator<Node<Z>>(head);}
    SllIterator<Node<Z>> end(){return SllIterator<Node<Z>>(nullptr);}

};



    



