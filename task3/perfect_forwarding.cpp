// ✅ 2. perfect_forwarding.cpp
// 实现：

// 一个通用工厂函数 createObject<T>(Args&&... args)，使用完美转发构造 T。
// 用它创建 string、vector<int>、自定义 Robot 类（带多参数构造函数）。
// 验证左值、右值参数均被正确转发。

#include <iostream>
#include <string>
#include <vector>

// 通用工厂函数，使用完美转发
template<typename T, typename... Args>
T createObject(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

// 自定义 Robot 类
class Robot {
public:
    Robot(std::string name, int id, double weight)
        : name_(std::move(name)), id_(id), weight_(weight) {
        std::cout << "Robot constructed: " << name_ << ", id=" << id_ << ", weight=" << weight_ << std::endl;
    }
    void info() const {
        std::cout << "Robot info: " << name_ << ", id=" << id_ << ", weight=" << weight_ << std::endl;
    }
private:
    std::string name_;
    int id_;
    double weight_;
};

int main() {
    // 测试 string
    std::string s1 = "hello";
    std::string s2 = createObject<std::string>(s1); // 左值
    std::string s3 = createObject<std::string>(std::string("world")); // 右值
    std::cout << "s2: " << s2 << ", s3: " << s3 << std::endl;

    // 测试 vector<int>
    std::vector<int> v1 = createObject<std::vector<int>>(5, 42); // 构造5个42
    std::cout << "v1:";
    for (int x : v1) std::cout << " " << x;
    std::cout << std::endl;

    // 测试 Robot
    std::string robotName = "R2D2";
    Robot r1 = createObject<Robot>(robotName, 101, 55.5); // 左值
    Robot r2 = createObject<Robot>(std::string("C3PO"), 102, 60.0); // 右值
    r1.info();
    r2.info();

    return 0;
}