////////////////对象的创建与销毁（栈对象 vs 堆对象）


//对象是类的实例化产物，每个对象有独立的成员变量（成员函数共享），生命周期由创建方式决定

//栈对象（自动对象）
//创建方式：直接声明（如Person p;），内存分配在栈区（栈是系统自动管理的内存区域）。
//生命周期：随作用域结束自动销毁（如函数返回、代码块结束）。
//销毁方式：系统自动调用析构函数。
//堆对象（动态对象）
//创建方式：用new关键字（如Person* p = new Person;），内存分配在堆区（堆是手动管理的内存区域）。
//生命周期：从new分配开始，到delete调用结束（若不手动 delete，内存一直占用）。
//销毁方式：必须手动调用delete，触发析构函数；数组堆对象用delete[]。

特性	    栈对象	           堆对象
内存区域	栈区（小，连续）	堆区（大，不连续）
创建语法	类名 对象名；	    类名 * 指针 = new 类名；
生命周期	作用域结束自动销毁	手动 delete 后销毁
销毁方式	系统自动调用析构	手动 delete 调用析构
访问方式	直接用.访问成员	    用->（指针）访问成员
风险	   栈溢出（对象过大时）	内存泄漏（忘记 delete）


#include <iostream>
using namespace std;

class Test {
public:
    Test() { cout << "Test构造函数：" << this << endl; }  // this指向当前对象
    ~Test() { cout << "Test析构函数：" << this << endl; }
};

// 栈对象演示
void stackObjDemo() {
    Test t1;  // 栈对象：进入函数时创建（栈区分配）
    Test t2;
    cout << "栈对象演示结束" << endl;
    // 函数返回时，栈对象t2、t1自动销毁（析构函数被调用）
}

// 堆对象演示
void heapObjDemo() {
    Test* p1 = new Test;  // 堆对象：new分配堆内存，调用构造
    Test* p2 = new Test[2];  // 堆数组对象：分配2个对象的内存
    
    cout << "堆对象演示结束" << endl;
    delete p1;  // 手动销毁单个堆对象，调用析构
    delete[] p2;  // 销毁堆数组对象，必须用delete[]（否则仅析构第一个）
}

int main() {
    cout << "=== 栈对象演示 ===" << endl;
    stackObjDemo();
    cout << "\n=== 堆对象演示 ===" << endl;
    heapObjDemo();
    return 0;
}









//1. 问题 1：堆对象忘记 delete 导致内存泄漏
//错误示例：Test* p = new Test;（无 delete）
//原因：堆内存不会自动释放，程序运行期间一直占用，直至程序结束。
//解决方案：遵循 “谁 new 谁 delete” 原则，或使用智能指针（unique_ptr/shared_ptr）自动管理。
//2. 问题 2：多次 delete 同一堆对象
//错误示例：Test* p = new Test; delete p; delete p;
//原因：第一次 delete 后，指针 p 成为 “悬垂指针”（指向已释放内存），第二次 delete 会触发内存崩溃。
//解决方案：delete 后将指针置空（p = nullptr;），避免重复释放。
//3. 问题 3：栈对象过大导致栈溢出
//错误示例：class BigObj { char buf[1024*1024*10]; }; BigObj obj;（10MB 栈对象）
//原因：栈区内存有限（Windows 默认 1MB，Linux 默认 8MB），过大对象会超出栈容量。
//解决方案：大对象用堆分配（new），或减少栈对象的内存占用。
//4. 问题 4：堆数组用 delete [] 而非 delete 
//错误示例：Test* p = new Test[3]; delete p;
//原因：delete 仅析构第一个对象，剩余 2 个对象的析构函数不会被调用，导致资源泄漏。
//解决方案：堆数组必须用delete[]销毁，与new[]配对。