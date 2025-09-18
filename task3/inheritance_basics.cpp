// ✅ 1. inheritance_basics.cpp
// 实现：

// 基类 RobotPart（含 virtual void operate() = 0; 和 virtual ~RobotPart() = default;）
// 派生类 Motor、Sensor、Camera
// 每个派生类重写 operate()，输出不同信息
// 在 main() 中用 RobotPart* 数组存储不同对象，遍历调用 operate()

#include <iostream>
#include <vector>

// 基类
class RobotPart {
public:
    virtual void operate() = 0;
    virtual ~RobotPart() = default;
};

// 派生类 Motor
class Motor : public RobotPart {
public:
    void operate() override {
        std::cout << "Motor is running." << std::endl;
    }
};

// 派生类 Sensor
class Sensor : public RobotPart {
public:
    void operate() override {
        std::cout << "Sensor is detecting." << std::endl;
    }
};

// 派生类 Camera
class Camera : public RobotPart {
public:
    void operate() override {
        std::cout << "Camera is capturing images." << std::endl;
    }
};

int main() {
    std::vector<RobotPart*> parts;
    parts.push_back(new Motor());
    parts.push_back(new Sensor());
    parts.push_back(new Camera());

    for (RobotPart* part : parts) {
        part->operate();
    }

    for (RobotPart* part : parts) {
        delete part;
    }
    return 0;
}