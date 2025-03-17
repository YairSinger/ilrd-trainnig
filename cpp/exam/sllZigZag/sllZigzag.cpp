#include <iostream>


class Node{
    public:
    int data;
    Node *next;
    Node(int data){
        this->data = data;
        this->next = NULL;
    }
};


Node *zigZag(Node *head){
   
    Node* headRunner = head; 
    Node* tailRunner = nullptr;

    if(head == nullptr || head->next == nullptr){
        return head;
    } 

    Node* temp = nullptr;
    Node* newTail = nullptr;
    while(headRunner != tailRunner){
        temp = headRunner->next;

        for(tailRunner = headRunner, newTail = nullptr; tailRunner->next != nullptr; tailRunner = tailRunner->next){
            if(tailRunner->next->next == nullptr){
                newTail = tailRunner->next;
            }
        }

        if(newTail != nullptr){
            headRunner->next = tailRunner;
            tailRunner->next = temp;
            newTail->next = nullptr;
            headRunner = temp;
        }
     
    }

    return head;
    } 




void printList(Node* head) {
    while (head) {
        std::cout << head->data << " -> ";
        head = head->next;
    }
    std::cout << "NULL" << std::endl;
}

void testZigZag() {
    // Creating a test linked list: 1 -> 2 -> 3 -> 4 -> 5 -> 6
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);

    std::cout << "Original List: ";
    printList(head);

    head = zigZag(head);

    std::cout << "ZigZag List: ";
    printList(head);
}

int main() {
    testZigZag();
    return 0;
}
