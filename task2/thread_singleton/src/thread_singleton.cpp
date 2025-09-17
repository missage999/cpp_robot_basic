#include "thread_singleton.h"

std::atomic<Singleton *> Singleton::instance{nullptr};
std::mutex Singleton::mtx;

Singleton *Singleton::getInstance()
{
    Singleton *tmp = instance.load(std::memory_order_relaxed);
    if (tmp == nullptr)
    {
        std::lock_guard<std::mutex> lock(mtx);
        tmp = instance.load(std::memory_order_relaxed);
        if (tmp == nullptr)
        {
            tmp = new Singleton();
            instance.store(tmp, std::memory_order_release);
        }
    }
    return tmp;
}