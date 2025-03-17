#ifndef THREAD_POOL_HPP
#define THREAD_POOL_HPP

#include "copilotWaitablePQ.hpp"
#include <atomic>
#include <thread> // worker
 
#include <functional> //task

template <typename V>
class FutureTask{
    public:

    FutureTask(ThreadPool::ITask& task);
    bool isDone(){
        return m_done;
    }

    V get(auto timeout = std::chrono::seconds(1)){
        std::unique_lock<std::mutex> lock(m_task->m_taskLock);   
                
        while(!m_done){
           if(std::cv_status::timeout == m_task->m_taskCondVar.wait_for(lock, timeout, [this](){ return m_done; })){
               return NULL;
           }
        }
        
        if(m_error){
            std::rethrow_exception(m_error);
        }
        lock.unlock;
        return m_result;
    }


    private:
        V m_result;
        std::exception m_error;
        std::shared_ptr<ThreadPool::ITask> m_task;
        bool m_done;

};

class ThreadPool
{
    public:
        
        class IWorker;
        template <typename V>
        class ITask;

       
        ThreadPool(size_t numOfThreads = 1);
        ~ThreadPool();// destroy all threads after current  running tasks are done
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool& operator=(const ThreadPool&) = delete;
        ThreadPool(ThreadPool&&) = delete;

        FutureTask<V> addTask(std::shared_ptr<ITask<V>> task);
        void pause(); //stops execution of new tasks from queue
        void resume(); //resume execution of tasks
        void terminate(); //terminates after  all tasks are done.
        void waitTerminantion(); //wait until all threads are done
    


    private:       
       WaitablePQ<ITask> m_tasks;
       std::atomic_int m_numThreads;
       std::atomic_bool m_isActive;
       std::mutex m_workersMutex;
       std::condition_variable m_workersCondVar;
      
};





class ThreadPool::ITask
{
    
    public:
         enum TaskPriority
        {
            LOW = 1,
            MEDIUM,
            HIGH
        };
        ITask(std::function <void()> runnable = NULL, TaskPriority priority = TaskPriority::MEDIUM);
        ITask(const ITask&) = delete;
        ITask& operator=(const ITask&);
        ~ITask() = default;
        virtual void execute();
        TaskPriority getPriority() const;
        bool operator<(const ITask& other) const
        {
            return getPriority() < other.getPriority();
        }
    private:
        TaskPriority m_priority;
        std::function <void()> m_runnable;
        std::mutex m_taskLock;
        std::condition_variable m_taskCondVar;

};
class ThreadPool::IWorker : private std::thread {
    public:
        IWorker(ThreadPool& pool);
        ~IWorker() = default;
        IWorker(const IWorker&) = delete;
        IWorker& operator=(const IWorker&) = delete;
        IWorker(IWorker&&) = delete;
        void run(); 
    private:
        bool m_isRunning;
        ThreadPool& m_pool;
     
};








#endif /* THREAD_POOL_HPP */