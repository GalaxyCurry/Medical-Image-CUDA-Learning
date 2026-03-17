// 类是数据（成员变量）和操作数据的行为（成员函数）的封装体，是创建对象的 “模板”。

class 类名 {
    访问控制符:
        成员变量;  // 数据成员（属性）
        成员函数声明;  // 成员方法（行为）
    访问控制符:
        成员变量;
        成员函数定义或声明;
};  // 注意分号结尾


//成员变量：类的属性，存储对象的状态（如人的姓名、年龄）；
//成员函数：类的行为，操作成员变量（如人的吃饭、说话），可在类内定义（自动 inline）或类外声明 + 定义。


访问控制符	类内访问	类外访问	子类访问（继承时）
public	       ✅	   ✅	      ✅
private	       ✅	   ❌	      ❌
protected	   ✅	   ❌	      ✅

//注意：若未指定访问控制符，class 默认 private，struct 默认 public（struct 与 class 仅默认访问权限不同）。

#include <iostream>
#include <string>
using namespace std;

// 类的定义
class Person {
private:
    // 私有成员：仅类内可访问（隐藏实现细节）
    string name;
    int age;

public:
    // 公有成员：类外可访问（暴露接口）
    // 成员函数类内声明，类外定义
    void setInfo(string n, int a);
    void showInfo();

protected:
    // 保护成员：类内+子类可访问
    string address;
};

// 成员函数类外定义（需加 类名:: 作用域限定符）
void Person::setInfo(string n, int a) {
    name = n;
    age = a;
    address = "中国";  // 类内可访问protected成员
}

void Person::showInfo() {
    cout << "姓名：" << name << "，年龄：" << age 
         << "，地址：" << address << endl;
}

int main() {
    Person p;
    // p.name = "张三";  // 错误：private成员类外不可访问
    // p.address = "北京";  // 错误：protected成员类外不可访问
    p.setInfo("张三", 20);  // 正确：通过public接口访问私有/保护成员
    p.showInfo();  // 输出：姓名：张三，年龄：20，地址：中国
    return 0;
}




三、常见问题与解决方案
1. 问题 1：类外直接访问 private/protected 成员
错误示例：p.name = "李四";
原因：违反封装原则，private/protected 成员不允许类外直接访问。
解决方案：通过 public 成员函数（如setInfo/getInfo）间接访问。
2. 问题 2：类外定义成员函数时忘记加类名::
错误示例：void setInfo(string n, int a) { ... }
原因：编译器认为是全局函数，而非类的成员函数。
解决方案：必须添加作用域限定符，明确归属类。
3. 问题 3：混淆 struct 与 class 的默认访问权限
错误示例：class Student { int id; }; Student s; s.id = 1001;（编译失败）
原因：class 默认 private，struct 默认 public。
解决方案：明确指定访问控制符，或根据需求选择 struct/class。