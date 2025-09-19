// ✅ 3. smart_pointers.cpp
// 实现：

// 用 unique_ptr 管理一个 RobotArm 类（含构造/析构函数，打印日志）。
// 用 shared_ptr 创建两个指向同一 Sensor 对象的指针，观察引用计数。
// 用 weak_ptr 打破 Parent-Child 循环引用（模拟机器人部件）。

#include <iostream>
#include <memory>

// RobotArm 类，使用 unique_ptr 管理
class RobotArm {
public:
    RobotArm() { std::cout << "RobotArm constructed\n"; }
    ~RobotArm() { std::cout << "RobotArm destructed\n"; }
};

// Sensor 类，使用 shared_ptr 管理
class Sensor {
public:
    Sensor() { std::cout << "Sensor constructed\n"; }
    ~Sensor() { std::cout << "Sensor destructed\n"; }
};

// Parent-Child 循环引用模拟
class Child; // 前向声明

class Parent {
public:
    std::shared_ptr<Child> child;
    Parent() { std::cout << "Parent constructed\n"; }
    ~Parent() { std::cout << "Parent destructed\n"; }
};

class Child {
public:
    std::weak_ptr<Parent> parent; // 用 weak_ptr 打破循环引用
    Child() { std::cout << "Child constructed\n"; }
    ~Child() { std::cout << "Child destructed\n"; }
};

int main() {
    // 1. unique_ptr 管理 RobotArm
    {
        std::unique_ptr<RobotArm> arm = std::make_unique<RobotArm>();
        // RobotArm 构造和析构日志会自动打印
    }

    // 2. shared_ptr 管理 Sensor
    {
        std::shared_ptr<Sensor> sensor1 = std::make_shared<Sensor>();
        std::cout << "sensor1 use_count: " << sensor1.use_count() << "\n";
        std::shared_ptr<Sensor> sensor2 = sensor1;
        std::cout << "sensor1 use_count after sensor2: " << sensor1.use_count() << "\n";
        std::cout << "sensor2 use_count: " << sensor2.use_count() << "\n";
    }

    // 3. weak_ptr 打破 Parent-Child 循环引用
    {
        std::shared_ptr<Parent> parent = std::make_shared<Parent>();
        std::shared_ptr<Child> child = std::make_shared<Child>();
        parent->child = child;
        child->parent = parent; // weak_ptr，不会增加引用计数
        std::cout << "parent use_count: " << parent.use_count() << "\n";
        std::cout << "child use_count: " << child.use_count() << "\n";
    }

    return 0;
}