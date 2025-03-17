#include <iostream>
#include <thread>
#include "copilotWaitablePQ.hpp"

struct elementForPQ{
    std::string name;
    int value;
    elementForPQ(std::string name, int value) : name(name), value(value) {}
    

};


void testEnqueueDequeue() {
    WaitablePQ<int> pq;
    pq.enqueue(5);
    pq.enqueue(10);
    pq.enqueue(3);

    int value;
    pq.dequeue(value);
    std::cout << "Dequeued value: " << value << std::endl; // Output: Dequeued value: 3

    pq.dequeue(value);
    std::cout << "Dequeued value: " << value << std::endl; // Output: Dequeued value: 5

    pq.dequeue(value);
    std::cout << "Dequeued value: " << value << std::endl; // Output: Dequeued value: 10
}

void testEmpty() {
    WaitablePQ<int> pq;
    std::cout << "Is empty? " << (pq.empty() ? "Yes" : "No") << std::endl; // Output: Is empty? Yes

    pq.enqueue(5);
    std::cout << "Is empty? " << (pq.empty() ? "Yes" : "No") << std::endl; // Output: Is empty? No

    int value;
    pq.dequeue(value);
    std::cout << "Is empty? " << (pq.empty() ? "Yes" : "No") << std::endl; // Output: Is empty? Yes
}

void testTimeout() {
    WaitablePQ<int> pq;
    int value;
    bool result = pq.dequeue(value, std::chrono::milliseconds(1000));
    std::cout << "Dequeue result: " << (result ? "Success" : "Timeout") << std::endl; // Output: Dequeue result: Timeout
}

void testMultiThreadsEnqueue() {
    WaitablePQ<int> pq;
    std::thread t1([&pq]() {
        pq.enqueue(5);
    });
    std::thread t2([&pq]() {
        pq.enqueue(10);
    });
    std::thread t3([&pq]() {
        pq.enqueue(3);
    });
    t1.join();
    t2.join();
    t3.join();

    int value;
    pq.dequeue(value);
    std::cout << "Dequeued value: " << value << std::endl; // Output: Dequeued value: 3
    pq.dequeue(value);
    std::cout << "Dequeued value: " << value << std::endl; // Output: Dequeued value: 5
    pq.dequeue(value);
    std::cout << "Dequeued value: " << value << std::endl; // Output: Dequeued value: 10
}

void testWaitingDequeue() {
    WaitablePQ<int> pq;
     pq.enqueue(11);
    pq.enqueue(15);
    pq.enqueue(19);
     std::thread t1([&pq]() {
        for(int i = 0; i < 4; i++) {
        int value;
         bool res = pq.dequeue(value, std::chrono::milliseconds(2000));
        std::cout << "Dequeued value: " <<(res ? "Success" : "Timeout") ;
        std::cout << "with value: " << value << std::endl;
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    pq.enqueue(23);
    t1.join();  

}

void testWaitablePQWithPairs() {
    WaitablePQ<std::pair<int, std::string>> pq;
    pq.enqueue(std::make_pair(5, "Five"));
    pq.enqueue(std::make_pair(10, "Ten"));
    pq.enqueue(std::make_pair(3, "Three"));
    std::pair<int, std::string> value;
    for (int i = 0; i < 3; i++) {
        bool res = pq.dequeue(value, std::chrono::milliseconds(1000));
        std::cout << "Dequeued value: " << (res ? "Success" : "Timeout") << std::endl;
        std::cout << "Dequeued value: " << value.first << " " << value.second << std::endl;
        
    }
}

void testElementPQ(){
    WaitablePQ<elementForPQ> pq;
    pq.enqueue(elementForPQ{"FiveQQ", 5});
    pq.enqueue(elementForPQ{"TenQQ", 10});
    pq.enqueue(elementForPQ{"ThreeQQ", 3});
    elementForPQ value(" ", 0);
    for (int i = 0; i < 3; i++) {
        bool res = pq.dequeue(value, std::chrono::milliseconds(1000));
        std::cout << "Dequeued value: " << (res ? "Success" : "Timeout") << std::endl;
        std::cout << "Dequeued value: " << value.name << " " << value.value << std::endl;
    }
}
int main() {
    testEnqueueDequeue();
    testEmpty();
    testTimeout();
    testMultiThreadsEnqueue();
    testWaitingDequeue();
    testWaitablePQWithPairs();
    testElementPQ();


    return 0;
}