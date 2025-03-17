#include <iostream>
#include <stdexcept>
#include <cassert>

// Node Structure
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T data) : data(data), next(nullptr) {}
};

// Iterator Class
template <typename T>
class LinkedListIterator {
public:
    LinkedListIterator(Node<T>* node) : current(node) {}

    // Dereference operator
    T& operator*() { return current->data; }

    // Arrow operator
    T* operator->() { return &current->data; }

    // Prefix increment
    LinkedListIterator& operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }

    // Postfix increment
    LinkedListIterator operator++(int) {
        LinkedListIterator temp = *this;
        ++(*this);
        return temp;
    }

    // Equality comparison
    bool operator!=(const LinkedListIterator& other) const {
        return current != other.current;
    }

    // Equality comparison for end iterator
    bool operator==(const LinkedListIterator& other) const {
        return current == other.current;
    }

private:
    Node<T>* current;
};

// Linked List Class
template <typename T>
class LinkedList {
public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Copy Constructor
    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
        Node<T>* current = other.head;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }

    // Copy Assignment Operator
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this == &other) {
            return *this;  // Handle self-assignment
        }

        // Clear current list
        clear();

        // Copy the elements from the other list
        Node<T>* current = other.head;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }

        return *this;
    }

    // Destructor to free memory
    ~LinkedList() {
        clear();
    }

    // Add element at the head
    void pushFront(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        ++size;
    }

    // Add element at the tail (for easier copy)
    void pushBack(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    // Remove element from the head
    void popFront() {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        --size;
    }

    // Return the size of the list
    size_t getSize() const {
        return size;
    }

    // Return the first element
    T& front() {
        if (size == 0) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    // Clear the list
    void clear() {
        while (head) {
            popFront();
        }
    }

    // Begin iterator (points to the head of the list)
    LinkedListIterator<T> begin() {
        return LinkedListIterator<T>(head);
    }

    // End iterator (points to nullptr)
    LinkedListIterator<T> end() {
        return LinkedListIterator<T>(nullptr);
    }

private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;
};

void testIncrementOperators() {
    LinkedList<int> list;
    list.pushFront(10);
    list.pushFront(20);
    list.pushFront(30);
    list.pushFront(40);
    list.pushFront(50);

    // Test for prefix increment (operator++)
    LinkedListIterator<int> it = list.begin();
    assert(*it == 50);  // First element
   std::cout << "prfix increasment" << *(++it) << std::endl;  
    assert(*it == 40);  // After prefix increment

    // Test for postfix increment (operator++(int))
    LinkedListIterator<int> it2 = list.begin();
    assert(*it2 == 50);  // First element
    std::cout << "postfix increasment" << *(it++) << std::endl;  
    it2++;
    assert(*it2 == 40);  // After postfix increment

    std::cout << "Prefix and Postfix increment tests passed!" << std::endl;
}

// Example Usage
int main() {
    // Create and populate the list
    LinkedList<int> list1;
    list1.pushFront(10);
    list1.pushFront(20);
    list1.pushFront(30);
    list1.pushFront(40);
    list1.pushFront(50);

    // Copy the list
    LinkedList<int> list2 = list1;  // Copy constructor
    LinkedList<int> list3;
    list3 = list1;  // Copy assignment

    // Print list1
    std::cout << "List 1 contents: ";
    for (auto it = list1.begin(); it != list1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Print list2 (copy)
    std::cout << "List 2 (copy) contents: ";
    for (auto it = list2.begin(); it != list2.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Print list3 (copy assignment)
    std::cout << "List 3 (copy assignment) contents: ";
    for (auto it = list3.begin(); it != list3.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

     testIncrementOperators();
    return 0;
}
