// ✅ 2. polymorphism_practice.cpp
// 实现：

// 基类 Shape（纯虚函数 area()）
// 派生类 Circle, Rectangle, Triangle
// 函数 double totalArea(vector<Shape*>& shapes) 计算总面积
// 测试：创建多个形状，计算总和

#include <iostream>
#include <vector>

class shape
{
public:
    virtual double area() const = 0;
    virtual ~shape() = default;
};

class circle : public shape
{
private:
    double radius;
public:
    circle(double r) : radius(r) {}
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class rectangle : public shape
{
private:
    double width, height;
public:
    rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
}; 

class triangle : public shape
{
private:
    double base, height;
public:
    triangle(double b, double h) : base(b), height(h) {}
    double area() const override {
        return 0.5 * base * height;
    }
};

double totalArea(const std::vector<shape*>& shapes) {
    double total = 0.0;
    for (const shape* s : shapes) {
        total += s->area();
    }
    return total;
}

int main() {
    std::vector<shape*> shapes;
    shapes.push_back(new circle(5.0));
    shapes.push_back(new rectangle(4.0, 6.0));
    shapes.push_back(new triangle(3.0, 4.0));

    std::cout << "Total area: " << totalArea(shapes) << std::endl;

    for (shape* s : shapes) {
        delete s;
    }
    return 0;
}