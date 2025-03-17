#include <thread>
#include <iostream>


class pingPong
{
public:
    void ping()
    {
       while(true){
        while (m_ping){}        
        std::cout << "Ping" << std::endl;
        m_ping = true;
       }
    void pong()
    {   
        while(!m_ping){}
        std::cout << "Pong" << std::endl;
        m_ping = false;
    }

private:
    volatile bool m_ping = true;

};


int main()
{
    pingPong pp;
    std::thread t1(&pingPong::ping, &pp);
    std::thread t2(&pingPong::pong, &pp);
    t1.join();
    t2.join();
    return 0;
}

