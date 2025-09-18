// 2. const_practice.cpp
// 实现一个 ImmutablePoint 类，所有访问函数均为 const
// 尝试对 const 对象调用非 const 函数，观察编译错误

#include <iostream>

class ImmutablePoint {
private:
    int x, y;
public:
    ImmutablePoint(int x_, int y_) : x(x_), y(y_) {}

    int getX() const { return x; }
    int getY() const { return y; }

    // 非 const 成员函数
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};

int main() {
    const ImmutablePoint p(3, 4);
    ImmutablePoint q(5, 6);
    std::cout << "x: " << p.getX() << ", y: " << p.getY() << std::endl;
    std::cout << "x: " << q.getX() << ", y: " << q.getY() << std::endl;

    // 以下两行会导致编译错误，因为 p 是 const 对象，不能调用非 const 成员函数
    // p.setX(10);
    // p.setY(20);

    return 0;
}