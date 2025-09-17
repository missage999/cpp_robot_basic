#include "thread_singleton.h"
#include <iostream>
#include <thread>

int main()
{
    auto task = []
    {
        Singleton *s = Singleton::getInstance();
        std::cout << s << std::endl; // 所有线程打印相同地址
    };

    std::thread t1(task);
    std::thread t2(task);
    std::thread t3(task);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}