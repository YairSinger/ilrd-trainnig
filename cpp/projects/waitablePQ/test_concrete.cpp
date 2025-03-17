void testWaitingDequeue() {
    // Create a waitable priority queue
    WaitablePriorityQueue<int> queue;

    // Enqueue some elements
    queue.enqueue(5);
    queue.enqueue(3);
    queue.enqueue(7);

    // Create a thread to dequeue elements
    std::thread dequeueThread([&]() {
        int value;
        queue.waitDequeue(value);
        std::cout << "Dequeued value: " << value << std::endl;
    });

    // Sleep for a while to allow the dequeue thread to start waiting
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Enqueue another element
    queue.enqueue(9);

    // Wait for the dequeue thread to finish
    dequeueThread.join();
}void testWaitingDequeue() {
    // Create a waitable priority queue
    WaitablePriorityQueue<int> queue;

    // Enqueue some elements
    queue.enqueue(5);
    queue.enqueue(3);
    queue.enqueue(7);

    // Create a thread to dequeue elements
    std::thread dequeueThread([&]() {
        int value;
        queue.waitDequeue(value);
        std::cout << "Dequeued value: " << value << std::endl;
    });

    // Sleep for a while to allow the dequeue thread to start waiting
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Enqueue another element
    queue.enqueue(9);

    // Wait for the dequeue thread to finish
    dequeueThread.join();
}

// Test case for waiting dequeue
TEST_CASE("Test waiting dequeue") {
    // Call the test function
    testWaitingDequeue();
}