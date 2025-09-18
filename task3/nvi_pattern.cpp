// ✅ 3. nvi_pattern.cpp
// 实现 NVI 模式：

// 基类 Task：
// 公有 void execute()
// 私有虚函数 void doExecute() = 0
// 在 execute() 中添加日志：“Task started…”, “Task finished.”
// 派生类 MoveTask, ScanTask 实现 doExecute()
// 测试调用，观察日志输出

#include <iostream>

class Task {
public:
    void execute() {
        std::cout << "Task started..." << std::endl;
        doExecute();
        std::cout << "Task finished." << std::endl;
    }
    virtual ~Task() = default;
private:
    virtual void doExecute() = 0;
};

class MoveTask : public Task {
private:
    void doExecute() override {
        std::cout << "Moving to the target location." << std::endl;
    }
};

class ScanTask : public Task {
private:
    void doExecute() override {
        std::cout << "Scanning the area." << std::endl;
    }
};

int main() {
    Task* move = new MoveTask();
    Task* scan = new ScanTask();

    move->execute();
    scan->execute();

    delete move;
    delete scan;
    return 0;
}
