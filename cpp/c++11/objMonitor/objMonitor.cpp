#include <iostream>
#include <list>
#include <functional> // For std::reference_wrapper


class IRunnable
{
public:
   virtual void run() = 0;
   virtual ~IRunnable() {}
    
};

class A : public IRunnable
{
public:
   virtual void run() {
   for (size_t i = 0; i < 1000; i++)
    {
        m_i += 1000;
        if(m_i % 80 == 0){
       std::cout << m_i << "A" << std::endl;
    }
   }}

private:
   int m_i;
};

class B : public IRunnable
{
public:
   virtual void run() {
        for (size_t i = 0; i < 1000; i++)
        {
            m_i += 1000;
            if(m_i % 80 == 0){
                std::cout << m_i << "B" << std::endl;
            }
            /* code */
        }
    
   }

private:
   int m_i;
};




class Monitor
{
private:
    std::list<std::reference_wrapper<IRunnable>> m_runnables;
public:
    void regCB(IRunnable& runnable) {
        m_runnables.push_back(runnable);
    }
    void monitor(){
        int count = 10;
        for (size_t i = 0; i < count; i++)
        {
           for(auto& runnable : m_runnables){
               runnable.get().run();
           }        
        }
    }
};



int main()
{
    Monitor monitor;
    A a;
    B b;
    monitor.regCB(a);
    monitor.regCB(b);
    monitor.monitor();
    return 0;
}


