#include <iostream>
#include "threadPool.hpp"
#include <chrono> // std::chrono::seconds

//******************  WORKER  *****************************

class WorkerTerminator : std::exception{};

ThreadPool::IWorker ::IWorker(ThreadPool& pool) : m_isRunning(true), m_pool(pool) {}

void  ThreadPool::IWorker::run(){
   ThreadPool::ITask task;
   while(true){
        m_pool.m_tasks.dequeue(task);
        try
        {
                task.execute();
        }
        catch(const WorkerTerminator& terminate){
            m_pool.m_numThreads--;
            this->detach();
        }
        catch(const std::exception& ignored){}         
   }
}


//******************  TASK  *****************************

ThreadPool::ITask::ITask(std::function <void()> runnable, TaskPriority priority)
    : m_runnable(runnable), m_priority(priority) {}

ThreadPool::ITask& ThreadPool::ITask::operator=(const ITask& other) {
    m_runnable = other.m_runnable;
    m_priority = other.m_priority;
    return *this;
}

ThreadPool::ITask::TaskPriority ThreadPool::ITask::getPriority() const {
    return m_priority;
}

void ThreadPool::ITask::execute(){
    m_runnable();
}


//******************* ThreadPool ****************************

using TaskPriority = ThreadPool::ITask::TaskPriority;

ThreadPool::ThreadPool(size_t numOfThreads = 1) : m_numThreads(numOfThreads), m_isActive(true), m_workersMutex(), m_workersCondVar()
{
    for(size_t i = 0; i < numOfThreads; i++){
        ThreadPool::IWorker worker(*this);
    }

}


void ThreadPool::addTask(std::shared_ptr<ITask> task){
    if (!m_isActive){
        throw std::runtime_error("ThreadPool is not active");
    }
    
    m_tasks.enqueue(*task);
}


void ThreadPool::pause(){
   if(m_isActive)
   {
        m_isActive = false;

      
        for (size_t i = 0; i < m_numThreads; i++)
        {
            TaskPriority maxPriority = static_cast<TaskPriority>(TaskPriority::HIGH + 1);
            
            ThreadPool::ITask waiterTask([this]->
                void{std::unique_lock<std::mutex> lock(m_workersMutex);
                m_workersCondVar.wait(lock, [this](){ return !m_isActive; });
                },maxPriority);

            m_tasks.enqueue(waiterTask);
        }
        }
}

void ThreadPool::resume(){
    if(!m_isActive)
    {
        m_isActive = true;
        m_workersCondVar.notify_all();
    }
}

void ThreadPool::waitTerminantion(){
    if(m_isActive){
        throw std::runtime_error("ThreadPool is still running");
    }
    
    std::unique_lock<std::mutex> lock(m_workersMutex);
    m_workersCondVar.wait(lock, [this]() { return m_numThreads == 0; });
}

void ThreadPool::terminate(){
    m_isActive = false;
    m_workersCondVar.notify_all();

    
    TaskPriority MinPriority = static_cast<TaskPriority>(TaskPriority::LOW - 1);

    for (size_t i = 0; i < m_numThreads; i++)
    {
       ThreadPool::ITask terminatorTask ([]()->void{throw WorkerTerminator();}, MinPriority);
       m_tasks.enqueue(terminatorTask);
    }
    
}


ThreadPool::~ThreadPool() 
{
    m_isActive = false;
    
    TaskPriority maxPriority = static_cast<TaskPriority>(TaskPriority::HIGH + 1);
    

    for (size_t i = 0; i < m_numThreads; i++)
    {
          
            ThreadPool::ITask waiterTask([this]->
                void{std::unique_lock<std::mutex> lock(m_workersMutex);
                m_workersCondVar.wait(lock, [this](){ return !m_isActive; });
                },maxPriority);

            m_tasks.enqueue(waiterTask);
           
    }
}
    

