#pragma once
#include <mutex>
#include <atomic>

class Singleton
{
private:
    static std::atomic<Singleton *> instance;
    static std::mutex mtx;
    Singleton() {}

public:
    static Singleton *getInstance();
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};

// static局部变量的初始化是线程安全的
//  class Singleton {
//  private:
//      Singleton() {} // 私有构造

// public:
//     static Singleton& getInstance() {
//         static Singleton instance; // C++11 保证线程安全！
//         return instance;
//     }

//     // 删除拷贝构造和赋值（防止复制）
//     Singleton(const Singleton&) = delete;
//     Singleton& operator=(const Singleton&) = delete;
// };