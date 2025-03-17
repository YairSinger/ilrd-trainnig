#ifndef WAITABLE_PQ_HPP
#define WAITABLE_PQ_HPP

#include <queue>
#include <mutex>
#include <chrono>
#include <condition_variable>

template <typename T>
class WaitablePQ
{
public:
    WaitablePQ(): m_mutex(), m_condVar(){
        m_queue = new std::priority_queue<T>();
    }
        
    
   // WaitablePQ& WaitablePQ(const WaitablePQ&);
    WaitablePQ& operator=(const WaitablePQ&);

    ~WaitablePQ(){
        delete m_queue;
    }
    void enqueue(T t){
       std::unique_lock<std::mutex> lock(m_mutex);
       m_queue.push(t);
        m_condVar.notify_all();
    }


    T dequeue( int timeoutSeconds = 10){
        std::unique_lock<std::mutex> lock(m_mutex);
        T temp = NULL;
        while(m_queue.empty()){
          if( m_condVar.wait_for(lock, std::chrono::seconds(timeoutSeconds)) == std::cv_status::timeout){
              return NULL;
          }
        }
        temp = m_queue.top();
        m_queue.pop();
        lock.unlock();
        return temp;
                
    }

    bool empty(){
        return m_queue.empty();
    }

private:
    std::priority_queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condVar;
};








#endif /* WAITABLE_PQ_HPP */