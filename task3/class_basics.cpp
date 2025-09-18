// 1. class_basics.cpp
// 实现一个 BankAccount 类，包含：
// 成员：accountNumber（string）、balance（double）
// 构造函数（带默认值）
// deposit()、withdraw() 方法
// getBalance() const 方法
// 拷贝构造函数（打印“拷贝构造被调用”）
// 移动构造函数（打印“移动构造被调用”）

#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    double balance;

public:
    // 构造函数（带默认值）
    BankAccount(const std::string& accNum = "000000", double bal = 0.0)
        : accountNumber(accNum), balance(bal) {}

    // 拷贝构造函数
    BankAccount(const BankAccount& other)
        : accountNumber(other.accountNumber), balance(other.balance) {
        std::cout << "拷贝构造被调用" << std::endl;
    }

    // 移动构造函数
    BankAccount(BankAccount&& other) noexcept
        : accountNumber(std::move(other.accountNumber)), balance(other.balance) {
        std::cout << "移动构造被调用" << std::endl;
        other.balance = 0.0;
    }

    // deposit 方法
    void deposit(double amount) {
        if (amount > 0) balance += amount;
    }

    // withdraw 方法
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    // getBalance 方法
    double getBalance() const {
        return balance;
    }

    // 打印账户信息
    void print() const {
        std::cout << "Account: " << accountNumber << ", Balance: " << balance << std::endl;
    }
};

int main() {
    BankAccount acc1("123456", 1000.0);
    acc1.deposit(500.0);
    acc1.withdraw(200.0);
    acc1.print();

    // 测试拷贝构造
    BankAccount acc2 = acc1;
    acc2.print();

    // 测试移动构造
    BankAccount acc3 = std::move(acc1);
    acc3.print();
    acc1.print(); // acc1 的余额应为 0

    return 0;
}