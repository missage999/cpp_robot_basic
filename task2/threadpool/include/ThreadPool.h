#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool
{
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;

public:
    ThreadPool(size_t threads)
    {
        for (size_t i = 0; i < threads; ++i)
        {
            workers.emplace_back([this]
                                 {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(mtx);
                        cv.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                    task(); // 执行任务
                } });
        }
    }

    template <class F>
    auto submit(F &&f) -> std::future<decltype(f())>
    {
        using return_type = decltype(f());
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::forward<F>(f));

        std::future<return_type> res = task->get_future();
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (stop)
                throw std::runtime_error("submit on stopped ThreadPool");
            tasks.emplace([task]()
                          { (*task)(); });
        }
        cv.notify_one();
        return res;
    }

    ~ThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for (std::thread &worker : workers)
        {
            worker.join();
        }
    }
};