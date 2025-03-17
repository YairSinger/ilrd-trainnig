#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <functional>
#include <vector>

class Scheduler {
public:
    static Scheduler& getInstance() {
        static Scheduler instance;
        return instance;
    }

    void start() {
        if (!running) {
            running = true;
            timerThread = std::thread(&Scheduler::timerLoop, this);
        }
    }

    void stop() {
        if (running) {
            running = false;
            timerThread.join();
        }
    }

    void schedule(std::function<void()> task, int delay_ms) {
        std::lock_guard<std::mutex> lock(mutex);
        tasks.push_back({task, std::chrono::steady_clock::now() + std::chrono::milliseconds(delay_ms)});
    }

private:
    struct Task {
        std::function<void()> task;
        std::chrono::time_point<std::chrono::steady_clock> time;
    };

    Scheduler() : running(false) {}

    void timerLoop() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust this for timer precision

            std::lock_guard<std::mutex> lock(mutex);
            auto now = std::chrono::steady_clock::now();
            for (auto it = tasks.begin(); it != tasks.end();) {
                if (it->time <= now) {
                    it->task();
                    it = tasks.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    std::vector<Task> tasks;
    std::thread timerThread;
    std::mutex mutex;
    bool running;
};

int main() {
    Scheduler& scheduler = Scheduler::getInstance();
    scheduler.start();

    scheduler.schedule([]() {
        std::cout << "Task 1 executed\n";
    }, 1000);

    scheduler.schedule([]() {
        std::cout << "Task 2 executed\n";
    }, 2000);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    scheduler.stop();

    return 0;
}
