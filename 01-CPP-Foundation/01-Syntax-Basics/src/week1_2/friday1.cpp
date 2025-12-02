///////////////////////////////拷贝构造函数（浅拷贝问题）


1. 拷贝构造函数的本质
拷贝构造函数是特殊的构造函数，用于用已有对象初始化新对象（如对象赋值、函数传值参数、函数返回对象），特点：
函数名与类名相同，无返回值；
唯一参数是 const 类名&（const 可选但推荐，引用必须有）；
若未自定义，编译器会自动生成 “默认拷贝构造函数”。
2. 拷贝构造函数的调用场景
用已有对象初始化新对象：Person p2(p1); 或 Person p2 = p1;；
函数参数为值传递：void func(Person p) { ... }（调用时拷贝实参到形参）；
函数返回值为值传递：Person func() { Person p; return p; }（返回时拷贝局部对象到返回值）。
3. 浅拷贝（默认拷贝构造的行为）
定义：浅拷贝仅复制对象的 “表面数据”（成员变量的直接值），对于指针成员，仅复制指针的地址（而非指针指向的堆数据）。
问题：当类有指针成员时，浅拷贝会导致两个对象的指针指向同一块堆内存，引发两大问题：
一个对象修改指针指向的数据，会影响另一个对象；
对象销毁时，会重复释放同一块堆内存（崩溃）。


#include <iostream>
#include <cstring>
using namespace std;

class Person {
private:
    char* name;  // 指针成员（指向堆内存）
    int age;

public:
    // 带参构造：分配堆内存
    Person(const char* n, int a) {
        cout << "构造函数：" << this << endl;
        age = a;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    // 未自定义拷贝构造函数（使用编译器默认浅拷贝）
    // ~Person() { delete[] name; }  // 若打开析构，会导致重复释放崩溃

    void setName(const char* n) {
        strcpy(name, n);  // 修改指针指向的堆数据
    }

    void showInfo() {
        cout << "地址：" << this << "，姓名：" << name << "，年龄：" << age << endl;
    }
};

int main() {
    Person p1("张三", 20);
    Person p2 = p1;  // 调用默认拷贝构造（浅拷贝）

    p1.showInfo();  // 输出：地址：0x7ffeefbff5e0，姓名：张三，年龄：20
    p2.showInfo();  // 输出：地址：0x7ffeefbff5d0，姓名：张三，年龄：20（name指针地址相同）

    // 问题1：一个对象修改，影响另一个
    p1.setName("张三修改");
    p1.showInfo();  // 输出：姓名：张三修改，年龄：20
    p2.showInfo();  // 输出：姓名：张三修改，年龄：20（p2的name也被改了）

    // 问题2：若打开析构函数，p1和p2销毁时都会delete[] name，导致重复释放崩溃
    return 0;
}






/////////////////////////常见问题与解决方案

1. 问题 1：默认浅拷贝导致重复释放堆内存（崩溃）
错误场景：类有指针成员，未自定义拷贝构造，且析构函数释放指针指向的堆内存。
原因：两个对象的指针指向同一块堆内存，销毁时两次 delete。
解决方案：自定义拷贝构造函数，实现深拷贝（后续周六重点）。


2. 问题 2：拷贝构造函数参数未用引用（导致无限递归）
错误示例：Person(Person p) { ... }（参数为值传递）
原因：调用拷贝构造时，值传递参数 p 需要先拷贝实参，又会调用拷贝构造，形成无限递归，最终栈溢出。
解决方案：参数必须用引用 Person(const Person& p)，引用传递不会触发拷贝构造。


3. 问题 3：拷贝构造函数参数未加 const
错误示例：Person(Person& p) { ... }
原因：无法用 const 对象初始化新对象（如const Person p1; Person p2 = p1; 编译失败）。
解决方案：参数添加 const 限定 const Person& p，既保护原对象不被修改，又支持 const 对象的拷贝。


4. 问题 4：混淆 “赋值运算符” 与 “拷贝构造”

Person p1("张三", 20);
Person p2;  // 调用默认构造
p2 = p1;  // 赋值运算符（不是拷贝构造）

原因：拷贝构造是 “初始化新对象”（对象不存在时），赋值运算符是 “给已有对象赋值”（对象已存在时）。
注意：默认赋值运算符也是浅拷贝，同样会引发指针成员的问题（后续需自定义赋值运算符）。



















































///////////////////////////////////////////////深拷贝实现（手动分配内存、拷贝数据）


1. 深拷贝的本质
深拷贝是针对浅拷贝问题的解决方案：对于指针成员，不复制指针地址，而是：
为新对象的指针成员手动分配一块新的堆内存；
将原对象指针指向的数据内容拷贝到新内存中；
两个对象的指针指向独立的堆内存，修改或销毁时互不影响。
2. 深拷贝的实现场景
类包含指针成员（如char*、int*）；
类包含动态分配的资源（如new创建的对象、文件句柄）；
必须同时自定义：拷贝构造函数 + 析构函数 + 赋值运算符（“三法则”），确保资源正确管理。
3. 深拷贝实现步骤
自定义拷贝构造函数（参数const 类名&）；
在拷贝构造中，为指针成员分配新的堆内存（大小与原对象指针指向的内存一致）；
将原对象指针指向的数据拷贝到新分配的内存中；
自定义析构函数，释放指针成员的堆内存；
（可选但推荐）自定义赋值运算符，避免赋值时的浅拷贝问题。


#include <iostream>
#include <cstring>
using namespace std;

class Person {
private:
    char* name;  // 指针成员（指向堆内存）
    int age;

public:
    // 1. 带参构造：分配堆内存
    Person(const char* n, int a) {
        cout << "构造函数：" << this << endl;
        age = a;
        name = new char[strlen(n) + 1];  // 分配内存（+1存'\0'）
        strcpy(name, n);  // 拷贝字符串
    }

    // 2. 自定义拷贝构造函数（深拷贝）
    Person(const Person& other) {
        cout << "拷贝构造函数（深拷贝）：" << this << endl;
        age = other.age;  // 拷贝普通成员
        // 深拷贝核心：为当前对象的name分配新内存
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);  // 拷贝原对象的字符串内容
    }

    // 3. 自定义赋值运算符（深拷贝，避免赋值时浅拷贝）
    Person& operator=(const Person& other) {
        cout << "赋值运算符（深拷贝）：" << this << endl;
        if (this == &other) {  // 防止自赋值（p1 = p1）
            return *this;
        }
        // 先释放当前对象的旧内存（避免内存泄漏）
        delete[] name;
        // 再分配新内存并拷贝数据
        age = other.age;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        return *this;  // 返回当前对象（支持链式赋值 p1 = p2 = p3）
    }

    // 4. 析构函数：释放堆内存
    ~Person() {
        cout << "析构函数：" << this << "，释放name内存" << endl;
        delete[] name;
        name = nullptr;
    }

    void setName(const char* n) {
        strcpy(name, n);
    }

    void showInfo() {
        cout << "地址：" << this << "，姓名：" << name << "，年龄：" << age << endl;
    }
};

int main() {
    // 场景1：用已有对象初始化新对象（拷贝构造）
    Person p1("张三", 20);
    Person p2 = p1;  // 调用深拷贝构造
    p1.setName("张三修改");
    p1.showInfo();  // 输出：姓名：张三修改，年龄：20
    p2.showInfo();  // 输出：姓名：张三，年龄：20（不受影响）

    // 场景2：对象赋值（赋值运算符）
    Person p3("李四", 25);
    p3 = p1;  // 调用深拷贝赋值运算符
    p3.showInfo();  // 输出：姓名：张三修改，年龄：20

    return 0;
}



1. 问题 1：深拷贝时忘记分配足够的内存
错误示例：name = new char[strlen(other.name)];（少加 1）
原因：字符串结束符'\0'需要额外 1 字节空间，未分配会导致字符串拷贝越界，内存污染。
解决方案：分配内存时必须 strlen(other.name) + 1。



2. 问题 2：赋值运算符中未处理自赋值

Person& operator=(const Person& other) {
    delete[] name;  // 自赋值时，先释放自身内存，再拷贝会访问已释放内存
    name = new char[strlen(other.name)+1];
    strcpy(name, other.name);
    return *this;
}


原因：自赋值（p1 = p1）时，先释放p1.name，再拷贝other.name（即p1.name），此时指针已悬垂。
解决方案：先判断this != &other，避免自赋值。



问题 3：赋值运算符中未释放旧内存

错误示例：
Person& operator=(const Person& other) {
    name = new char[strlen(other.name)+1];  // 未释放旧内存
    strcpy(name, other.name);
    return *this;
}

原因：新对象的name原本指向的堆内存未释放，导致内存泄漏。
解决方案：赋值前先释放当前对象的旧内存（delete[] name）。



4. 问题 4：深拷贝不完整（仅拷贝部分指针成员）
错误示例：类有多个指针成员（如char* name; int* scores;），拷贝构造仅处理了name，未处理scores。
原因：未处理的指针成员仍为浅拷贝，导致部分资源重复释放或修改冲突。
解决方案：所有指针成员都必须实现深拷贝，确保每个动态资源都独立分配。





























///////////////////////////////////////////////this 指针（作用、使用场景）

1. this 指针的本质
this是成员函数中隐含的常量指针（类名* const this），指向当前调用该成员函数的对象，特点：
隐藏在每个非静态成员函数中（无需声明，直接使用）；
不能显式修改this的指向（因为是const指针）；
静态成员函数中没有this指针（静态成员函数属于类，不属于某个对象）；
this指针的类型：
普通成员函数：类名* const this（可修改this指向的对象内容）；
const 成员函数：const 类名* const this（不能修改对象内容）。
2. this 指针的核心作用
区分成员变量与局部变量（同名时）；
从成员函数中返回当前对象（实现链式调用）；
访问当前对象的成员（显式使用，增强代码可读性）；
在类的内部调用其他成员函数（隐含使用this）。






#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;

public:
    // 场景1：区分成员变量与局部变量（同名）
    Person(string name, int age) {
        this->name = name;  // this->name：成员变量；name：参数（局部变量）
        this->age = age;
    }

    // 场景2：返回当前对象（*this），实现链式调用
    Person& setName(string name) {
        this->name = name;
        return *this;  // 返回当前对象的引用（支持链式调用）
    }

    Person& setAge(int age) {
        this->age = age;
        return *this;
    }

    // 场景3：const成员函数（this指针类型为const Person* const）
    void showInfo() const {
        // this->name = "李四";  // 错误：const成员函数不能修改对象内容
        cout << "姓名：" << this->name << "，年龄：" << this->age << endl;
    }

    // 场景4：显式访问当前对象的成员（增强可读性）
    void printThis() {
        cout << "当前对象地址：" << this << endl;  // this指向当前对象
    }
};

int main() {
    Person p("张三", 20);
    p.printThis();  // 输出：当前对象地址：0x7ffeefbff5e0（与p的地址相同）

    // 链式调用（setName返回*this，可继续调用setAge）
    p.setName("李四").setAge(25);
    p.showInfo();  // 输出：姓名：李四，年龄：25

    const Person p2("王五", 30);
    p2.showInfo();  // 正确：const对象只能调用const成员函数
    // p2.setName("赵六");  // 错误：const对象不能调用非const成员函数

    return 0;
}























1. 问题 1：在静态成员函数中使用 this 指针

错误示例：
class Test {
public:
    static void func() {
        cout << this << endl;  // 编译错误：静态成员函数无this指针
    }
};

原因：静态成员函数属于 “类”，而非某个具体对象，调用时没有对象实例，因此没有 this 指针。
解决方案：静态成员函数中不能使用 this，也不能访问非静态成员（非静态成员依赖对象实例）。



2. 问题 2：const 成员函数中修改对象内容

错误示例：
void showInfo() const {
    age = 30;  // 错误：const成员函数的this是const指针，不能修改对象
}

原因：const 成员函数的 this 指针类型是const 类名* const，限制了不能修改对象的成员变量。
解决方案：若需修改成员变量，将该成员声明为mutable（突破 const 限制），或移除函数的 const 限定。



3. 问题 3：返回 this 指针时返回值类型错误

错误示例：
Person setName(string name) {  // 返回值为值类型
    this->name = name;
    return *this;  // 拷贝当前对象返回，链式调用修改的是临时对象
}
p.setName("李四").setAge(25);  // setAge修改的是临时对象，p的年龄不变

原因：返回值为值类型时，会拷贝当前对象生成临时对象，链式调用修改的是临时对象，而非原对象。
解决方案：返回值类型改为引用（Person&），直接返回当前对象的引用，链式调用修改原对象。





4. 问题 4：误用 this 指针访问静态成员

错误示例：

class Test {
public:
    static int count;
    void func() {
        this->count = 10;  // 语法允许，但不推荐
    }
};

原因：静态成员属于类，无需通过对象（this）访问，直接用类名::count更清晰。
解决方案：访问静态成员时，优先使用类名::静态成员名，避免通过 this 指针（易混淆静态 / 非静态成员）。