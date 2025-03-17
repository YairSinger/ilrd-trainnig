#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

template < typename T>
class WaitablePQ
{
public:
    WaitablePQ() = default;
    ~WaitablePQ() = default;

    void enqueue(T& t){
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(t);
        m_condVar.notify_one();
    }

    bool dequeue(T& t, const std::chrono::milliseconds timeout = std::chrono::milliseconds::max()) {
        std::unique_lock<std::mutex> lock(m_mutex);
        if(!m_condVar.wait_for(lock, timeout, [this](){ return !m_queue.empty(); })) {
            return false; // Timeout
        }
        t = m_queue.top();
        m_queue.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

private:
    std::priority_queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_condVar;
};