// 3. static_member.cpp
// 实现 Student 类，统计创建的学生总数（static 成员）
// 提供静态方法 getTotalStudents()

#include <iostream>
using namespace std;

class Student {
private:
    static int totalStudents;
public:
    Student() {
        ++totalStudents;
    }
    static int getTotalStudents() {
        return totalStudents;
    }
};

// 静态成员变量定义和初始化
int Student::totalStudents = 0;

int main() {
    Student s1;
    Student s2;
    Student s3;
    cout << "Total students: " << Student::getTotalStudents() << endl;
    Student s4;
    cout << "Total students: " << Student::getTotalStudents() << endl;
    return 0;
}