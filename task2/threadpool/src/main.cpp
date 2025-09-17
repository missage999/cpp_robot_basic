#include "ThreadPool.h"
#include <iostream>

int main()
{
    ThreadPool pool(4); // 4个线程

    auto f1 = pool.submit([]
                          {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return 42; });

    auto f2 = pool.submit([]
                          { return std::string("Hello from thread!"); });

    std::cout << f1.get() << std::endl; // 42
    std::cout << f2.get() << std::endl; // Hello from thread!

    return 0;
}