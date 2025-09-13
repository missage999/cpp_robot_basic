/**
 * 目标：对比 raw pointer、shared_ptr、unique_ptr 的使用
 * 要求：1. 无内存泄漏  2. 用 valgrind 检测通过
 */
#include <iostream>
#include <memory>

class Robot {
public:
    Robot()  { std::cout << "Robot constructed\n"; }
    ~Robot() { std::cout << "Robot destroyed\n"; }
    void speak() const { std::cout << "Beep boop\n"; }
};

// TODO 1：返回裸指针，调用者易忘 delete
Robot* createRawRobot() {
    return new Robot();
}

// TODO 2：返回 unique_ptr，独占所有权
std::unique_ptr<Robot> createUniqueRobot() {
    return std::make_unique<Robot>();   // 已 OK
}

// TODO 3：返回 shared_ptr，共享所有权
std::shared_ptr<Robot> createSharedRobot() {
    // 请用 std::make_shared 实现
    return std::make_shared<Robot>();
}

int main() {
    std::cout << "=== raw pointer ===\n";
    // 调用 createRawRobot，使用完后手动 delete
    auto ptr=createRawRobot();
    ptr->speak();
    delete ptr;

    std::cout << "\n=== unique_ptr ===\n";
    auto u = createUniqueRobot();
    u->speak();

    std::cout << "\n=== shared_ptr ===\n";
    auto s1 = createSharedRobot();
    auto s2 = s1;               // 共享
    s1->speak();

    return 0;
}