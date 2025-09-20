// ✅ 3. constexpr_concepts.cpp
// 实现：

// constexpr 斐波那契函数，用于初始化 array。
// 自定义 Addable Concept，约束加法函数模板。
// 使用 std::integral Concept 重载不同整数类型的处理函数。

#include <array>
#include <concepts>
#include <iostream>

// constexpr 斐波那契函数
constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// 用 constexpr 初始化 array
constexpr std::array<int, 10> fib_array = []{
    std::array<int, 10> arr = {};
    for (size_t i = 0; i < arr.size(); ++i)
        arr[i] = fibonacci(static_cast<int>(i));
    return arr;
}();

// 自定义 Addable Concept
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

// 加法函数模板
template<Addable T>
T add(T a, T b) {
    return a + b;
}

// 使用 std::integral Concept 重载处理函数
void process(std::integral auto value) {
    std::cout << "Integral value: " << value << std::endl;
}

void process(double value) {
    std::cout << "Double value: " << value << std::endl;
}

// 测试代码
int main() {
    std::cout << "Fibonacci array: ";
    for (auto v : fib_array)
        std::cout << v << ' ';
    std::cout << std::endl;

    int a = 5, b = 7;
    double x = 2.5, y = 3.5;
    std::cout << "add(int, int): " << add(a, b) << std::endl;
    std::cout << "add(double, double): " << add(x, y) << std::endl;

    process(42);
    process(3.14);

    return 0;
}