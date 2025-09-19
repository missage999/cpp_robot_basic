// ✅ 1. template_basics.cpp
// 实现：

// 函数模板 printContainer(Container c)，能打印任何支持 begin()/end() 的容器。
// 类模板 Stack<T>，用 vector<T> 实现（支持 push, pop, top, empty）。
// 特化 Stack<bool>，内部用 vector<char> 优化存储。

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename Container>
void printContainer(const Container &c)
{
    for (const auto &elem : c)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template <typename T>
class Stack
{
private:
    std::vector<T> elems;

public:
    void push(const T &value)
    {
        elems.push_back(value);
    }
    void pop()
    {
        if (elems.empty())
        {
            throw std::out_of_range("Stack<>::pop(): empty stack");
        }
        elems.pop_back();
    }
    T top() const
    {
        if (elems.empty())
        {
            throw std::out_of_range("Stack<>::top(): empty stack");
        }
        return elems.back();
    }
    bool empty() const
    {
        return elems.empty();
    }
};

// 特化 Stack<bool>
template <>
class Stack<bool>
{
private:
    std::vector<char> elems; // 使用 char 来优化存储
public:
    void push(bool value)
    {
        elems.push_back(value ? 1 : 0);
    }
    void pop()
    {
        if (elems.empty())
        {
            throw std::out_of_range("Stack<bool>::pop(): empty stack");
        }
        elems.pop_back();
    }
    bool top() const
    {
        if (elems.empty())
        {
            throw std::out_of_range("Stack<bool>::top(): empty stack");
        }
        return elems.back() != 0;
    }
    bool empty() const
    {
        return elems.empty();
    }
};

int main()
{
    // 测试 printContainer
    std::vector<int> vec = {1, 2, 3, 4, 5};
    printContainer(vec);

    std::vector<std::string> strVec = {"hello", "world"};
    printContainer(strVec);

    // 测试 Stack<int>
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    std::cout << "Top of intStack: " << intStack.top() << std::endl;
    intStack.pop();
    std::cout << "Top of intStack after pop: " << intStack.top() << std::endl;

    // 测试 Stack<bool>
    Stack<bool> boolStack;
    boolStack.push(true);
    boolStack.push(false);
    std::cout << "Top of boolStack: " << boolStack.top() << std::endl;
    boolStack.pop();
    std::cout << "Top of boolStack after pop: " << boolStack.top() << std::endl;

    return 0;
}