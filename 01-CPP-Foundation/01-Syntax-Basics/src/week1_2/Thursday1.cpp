////////////////////////////析构函数（资源释放、默认析构局限性）

1. 析构函数的本质
析构函数是类的特殊成员函数，用于对象销毁时的 “清理工作”（如释放堆内存、关闭文件、断开网络连接等），特点：
无返回值（连void都不能写）；
函数名是~类名（波浪号 + 类名）；
无参数、不能重载（一个类只能有一个析构函数）；
对象销毁时自动调用（栈对象作用域结束、堆对象 delete 时）。
2. 默认析构函数
编译器自动生成：若类中未定义析构函数，编译器会生成 “默认析构函数”。
局限性：默认析构函数仅会销毁对象本身（释放成员变量占用的内存），但不会释放成员变量指向的堆内存（如指针成员指向的堆空间），导致内存泄漏。
3. 析构函数的核心作用：资源释放
当类包含 “动态分配的资源”（如new分配的堆内存、文件句柄、网络套接字）时，必须自定义析构函数，在对象销毁前释放这些资源。





#include <iostream>
#include <cstring>
using namespace std;

class Student {
private:
    char* name;  // 指针成员（指向堆内存）
    int id;

public:
    // 带参构造：new分配堆内存存储姓名
    Student(int sid, const char* n) {
        cout << "Student构造函数：" << this << endl;
        id = sid;
        name = new char[strlen(n) + 1];  // 分配堆内存（+1存'\0'）
        strcpy(name, n);  // 拷贝字符串
    }

    // 自定义析构函数：释放堆内存（解决默认析构的局限性）
    ~Student() {
        cout << "Student析构函数：" << this << "，释放name内存" << endl;
        delete[] name;  // 释放指针指向的堆内存
        name = nullptr;  // 避免悬垂指针
    }

    void showInfo() {
        cout << "学号：" << id << "，姓名：" << name << endl;
    }
};

int main() {
    // 栈对象：作用域结束时自动调用析构
    Student s1(1001, "张三");
    s1.showInfo();

    // 堆对象：delete时调用析构
    Student* s2 = new Student(1002, "李四");
    s2->showInfo();
    delete s2;  // 手动释放，触发析构

    return 0;
}









// 三、常见问题与解决方案

问题 1：默认析构导致内存泄漏

class Test {
public:
    int* p;
    Test() { p = new int[10]; }  // new分配堆内存
    // 未自定义析构函数（使用默认析构）
};
Test t;  // 对象销毁时，默认析构仅销毁t本身，p指向的堆内存未释放

原因：默认析构不处理指针成员指向的堆资源。
解决方案：自定义析构函数，显式delete动态分配的资源。



问题 2：析构函数中重复释放资源

~Test() {
    delete[] p;
    delete[] p;  // 重复释放
}

原因：第一次 delete 后，p 是悬垂指针，第二次 delete 会导致内存崩溃。
解决方案：释放后将指针置空（p = nullptr;），delete nullptr 是安全的（无操作）。



问题 3：继承时析构函数未声明为 virtual（后续继承重点）

class Parent { ~Parent() { ... } };  // 非虚析构
class Child : public Parent { ~Child() { ... } };
Parent* p = new Child;
delete p;  // 仅调用Parent析构，Child析构未调用，导致Child的资源泄漏

原因：非虚析构时，delete 基类指针仅调用基类析构。
解决方案：基类析构函数声明为virtual ~Parent() { ... }，子类析构自动成为虚析构。



问题 4：析构函数中操作已释放的资源

~Student() {
    cout << "姓名：" << name << endl;  // 先访问name，再释放
    delete[] name;
}

风险：若 name 已被意外修改（如野指针），访问时会崩溃。
解决方案：析构函数中先释放资源，再执行其他操作（或避免访问已释放资源）。