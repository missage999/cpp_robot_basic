#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> data_queue;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;

void producer()
{
    for (int i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        {
            std::lock_guard<std::mutex> lock(mtx);
            data_queue.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        cv.notify_one(); // 通知消费者
    }
    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all(); // 通知所有消费者结束
}

void consumer(int id)
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []
                { return !data_queue.empty() || finished; }); // 等待条件满足
        if (finished && data_queue.empty())
            break;
        int value = data_queue.front();
        data_queue.pop();
        lock.unlock(); // 提前解锁，减少临界区
        std::cout << "Consumer " << id << " consumed: " << value << std::endl;
    }
}

int main()
{
    std::thread p(producer);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    p.join();
    c1.join();
    c2.join();
    return 0;
}