// ✅ 4. adapters_practice.cpp
// 实现：

// 用 stack 模拟“撤销操作”（记录最近 3 次操作名称）。
// 用 priority_queue 模拟“机器人任务调度”（任务带优先级）。
// 用 back_inserter 将一个 vector 的平方值插入另一个 vector。

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>

int main() {
    // 用 stack 模拟“撤销操作”（记录最近 3 次操作名称）。
    std::stack<std::string> undoStack;
    undoStack.push("Move Forward");
    undoStack.push("Turn Left");
    undoStack.push("Pick Object");

    std::cout << "撤销操作（最近 3 次）:" << std::endl;
    while (!undoStack.empty()) {
        std::cout << undoStack.top() << std::endl;
        undoStack.pop();
    }

    // 用 priority_queue 模拟“机器人任务调度”（任务带优先级）。
    struct Task {
        int priority;
        std::string name;
        // priority_queue 默认大顶堆
        bool operator<(const Task& other) const {
            return priority < other.priority;
        }
    };

    std::priority_queue<Task> taskQueue;
    taskQueue.push({2, "Charge Battery"});
    taskQueue.push({5, "Deliver Package"});
    taskQueue.push({3, "Scan Area"});

    std::cout << "\n任务调度（按优先级）:" << std::endl;
    while (!taskQueue.empty()) {
        std::cout << "Priority " << taskQueue.top().priority << ": " << taskQueue.top().name << std::endl;
        taskQueue.pop();
    }

    // 用 back_inserter 将一个 vector 的平方值插入另一个 vector。
    std::vector<int> src = {1, 2, 3, 4};
    std::vector<int> dst;
    std::transform(src.begin(), src.end(), std::back_inserter(dst),
                   [](int x) { return x * x; });

    std::cout << "\n平方值插入结果:" << std::endl;
    for (int v : dst) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    return 0;
}