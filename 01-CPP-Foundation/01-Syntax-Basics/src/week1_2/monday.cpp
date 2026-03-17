# include <iostream>
# include <string>
# include <cmath>
# include <limits>
using namespace std;


/* int main(){

    int arr[5] = {0};

    arr [4] = 10;
    arr [3] = 5;
    arr [2] = 2;
    arr [1] = 1;


    std::cout << arr << std::endl;
    std::cout << arr[3] << std::endl;
    std::cout << arr[4] << std::endl;

    for(int i = 0; i<5; i++){
        std::cout << arr[i] << std::endl;
    }

    std::cout << "Hi!" << std::endl;
    return 0;
}
 */



 
// 返回类型 函数名（参数1类型 参数1名， 参数2类型，参数2名，....）{
//     函数体
//     return 返回值}  定义调用传参


//函数1内部调用函数2时需要在此函数1前面定义或者声明使用此函数2



//命名空间是一种将标识符（变量名，函数名，类名等）分组的机制，防止命名冲突
//std是标准命名空间，包含C++标准库的所有标识符
//namespace namespace_name{
//     int varl;
//     void func1();
//     namespace sub-namespace{
//         content
//     }
// }   在函数1外使用命名空间内的标识符时需要使用命名空间名作为前缀，格式为namespace_name::varl;  namespace_name::func1();   namespace_name::sub-namespace::content;
//     using namespace namespace_name;  使用using声明后可以直接使用命名空间内的标识符而不需要前缀
//     ::是作用域解析运算符，用于访问特定命名空间或类中的成员




// 变量名
int age = 18;
double gpa = 3.5;
char Name = 'A';
// 非法变量名
// int 123num; // 不能以数字开头
// double my-gpa; // 不能包含连字符
// char first name; // 不能包含空格
// int return; // 不能使用关键字



// 数据类型 1 Byte（字节） = 8 bits（位）
// unsigned 是修饰符（仅用于整数类型）

// 整数类型
// 字符（1 Byte）
// signed char（有符号）: 1 Byte，范围 -128 到 127
// unsigned char（无符号）: 1 Byte，范围 0 到 255
// 实际大小用 sizeof 运算符获取

// 整型 int（通常 4 Byte）
// 默认 signed int，范围 -2,147,483,648 到 2,147,483,647 (-2^31 ~2^31 - 1)
// unsigned int，范围 0 到 4,294,967,295 (2^32 - 1)


// 短整型 short int（通常 2 Byte）
// 默认 signed short int，范围 -32,768 到 32,767 (-2^15 ~ 2^15 - 1)
// unsigned short int，范围 0 到 65,535 (2^16 - 1)

// 长整型 long int（通常 4 或 8 Byte，取决于系统）
// 默认 signed long int，范围至少 -2,147,483,648 到 2,147,483,647
// unsigned long int，范围至少 0 到 4,294,967,295

// 浮点类型
// 单精度 float（通常 4 Byte）  
// 范围约为 1.2E-38 到 3.4E+38，精度约为 7 位十进制数字
// 双精度 double（通常 8 Byte）
// 范围约为 2.3E-308 到 1.7E+308，精度约为 15 位十进制数字
// 长双精度 long double（通常 10、12 或 16 Byte，取决于系统）
// 范围和精度取决于具体实现，通常比 double 更高

//// 精度误差示例
double a = 0.1 + 0.2;
//std::cout << a << std::endl; // 输出 0.30000000000000004（而非 0.3）



//unsigned int x = 4294967295; // unsigned int 最大值
//x++;
//cout << x << endl; // 输出 0（溢出后循环到最小值）

//unsigned int y = 0;
//y--;
//cout << y << endl; // 输出 4294967295（下溢后循环到最大值）




//const 常量的核心特性
//必须初始化（定义时赋值，否则编译错误）；
//初始化后不可修改（强行修改会编译报错或触发未定义行为）；
//有类型检查（比宏定义更安全）；
//有作用域（局部 const 作用于函数 / 代码块，全局 const 作用于整个文件）

// 1. 局部 const 常量（栈上存储）
const int MAX_AGE = 120; // 必须初始化
// MAX_AGE = 130; // 编译错误：const 变量不可修改

// 2. 全局 const 常量（只读数据区存储，默认内部链接）
const double PI = 3.1415926535;

// 3. const 修饰数组大小（C++ 支持，C 不支持）
const int ARR_SIZE = 5;
int arr[ARR_SIZE] = {1,2,3,4,5}; // 合法




//特性	const 常量	#define 宏定义
//本质	不可修改的变量（占内存）	预处理阶段文本替换（不占内存）
//类型检查	有（编译时检查，更安全）	无（仅替换，易出错）
//作用域	有（局部 / 全局）	无（从定义处到文件结束）
//示例	const int N = 10;	#define N 10

#define N 10 + 2
int a = N * 3; // 预处理后为 10 + 2 * 3 = 16（而非 (10+2)*3=36）

const int M = 10 + 2;
int b = M * 3; // 正确：12 * 3 = 36（编译时计算常量值）








//const int* p：指针指向的内容不可修改（指针可变）；
//int* const p：指针本身不可修改（指向的内容可变）；
//const int* const p：指针和指向的内容均不可修改

//int x = 10, y = 20;
//const int* p = &x;
// *p = 15; // 错误：指向的内容不可修改
//p = &y; // 合法：指针本身可变

//int* const q = &x;
//*q = 15; // 合法：指向的内容可变
// q = &y; // 错误：指针本身不可修改











//函数重载的唯一判断依据是 参数列表（形参的类型、个数、顺序）

// 错误：仅返回值不同，不构成重载
//int add(int a, int b) { return a + b; }
//double add(int a, int b) { return a + b + 0.0; }

// 错误：仅形参名称不同，不构成重载
//int add(int a, int b) { return a + b; }
//int add(int x, int y) { return x + y; }

//对于值传递参数（如 int）：const int a 和 int a 视为同一类型，不构成重载；
//对于引用 / 指针参数（如 int&、int*）：const int& a 和 int& a 是不同类型，构成重载

// 1个参数，无默认值
//void func(int a) { cout << "func(int)" << endl; }
// 2个参数，第二个有默认值
//void func(int a, int b = 0) { cout << "func(int, int)" << endl; }
/* int main() {
    func(10);  // 错误：编译器无法确定调用哪个（可匹配第一个，或第二个省略 b）
    return 0;
} */





#include <iostream>
using namespace std;

// 传值调用：形参a是实参x的拷贝
void add_val(int a) {
    a += 10; // 仅修改拷贝本
    cout << "函数内（传值）：a = " << a << endl; // 输出 20
}

int main() {
    int x = 10;
    add_val(x); // 传递x的拷贝，而非x本身
    cout << "函数外（传值）：x = " << x << endl; // 输出 10（实参未变）
    return 0;
}
// 无需修改实参、实参是小体量数据（如 int、char）
// 优点：简单安全（不会意外修改实参）；
// 缺点：存在拷贝开销（实参越大，开销越大）；无法修改实参。




// 传址调用：形参p是存储x地址的指针
void add_ptr(int* p) {
    *p += 10; // 解引用指针，修改指针指向的实参内存
    cout << "函数内（传址）：*p = " << *p << endl; // 输出 20
    cout << "指针p存储的地址：" << p << endl;      // 输出x的内存地址
}


int main() {
    int x = 10;
    add_ptr(&x); // 传递x的地址（&是取地址符）
    cout << "函数外（传址）：x = " << x << endl;   // 输出 20（实参被修改）
    cout << "x的内存地址：" << &x << endl;         // 与p存储的地址一致
    return 0;
}
// 需要修改实参、实参是大体量数据（避免拷贝）、允许传递空值（NULL）
// 优点：无拷贝开销（仅传递 8 字节地址，与实参大小无关）；可修改实参；支持空指针（如 add_ptr(NULL)，需函数内判断避免崩溃）；
// 缺点：语法复杂（需手动解引用）；存在空指针风险（需检查 if (p != NULL)）；可能意外修改实参



// 传引用调用：形参r是实参x的别名
void add_ref(int& r) {
    r += 10; // 操作别名，等同于操作x
    cout << "函数内（传引用）：r = " << r << endl; // 输出 20
    cout << "引用r的地址：" << &r << endl;         // 与x的地址一致
}

int main() {
    int x = 10;
    add_ref(x); // 直接传递实参，无需&
    cout << "函数外（传引用）：x = " << x << endl; // 输出 20（实参被修改）
    cout << "x的内存地址：" << &x << endl;         // 与&r一致
    return 0;
}
// 需要修改实参、实参是大体量数据（避免拷贝）、不允许传递空值（更安全）
// 优点：无拷贝开销（与传址一致）；语法简洁（无需解引用）；安全性高（不能为 NULL，无空指针风险）；
// 缺点：不能绑定空值（必须初始化绑定实参）；不能重新绑定其他变量（一旦绑定，终身关联）；可能意外修改实参（需用 const 修饰只读引用）


//对比维度	        传值调用	           传址调用（指针）	                  传引用调用
//参数传递方式	    传递实参的拷贝	        传递实参的内存地址	               传递实参的别名（共享内存）
//实参是否可修改	    不可修改（仅改拷贝本）	 可修改（解引用指针）	            可修改（操作别名）
//内存开销	       实参大小（拷贝成本）	     固定 8 字节（指针大小）	        几乎为 0（无拷贝）
//语法形式	       直接传实参（func(x)）	传地址（func(&x)），需解引用（*p）	直接传实参（func(x)），无需解引用
//空值支持	       不支持（必须传具体值）	支持（可传NULL/nullptr）	        不支持（必须绑定有效实参）
//重新绑定其他变量	无（形参是独立变量）	 可（p = &y，指向新地址）	         不可（一旦绑定，无法修改）
//安全性	           高（无副作用）	        中（需检查空指针）	                高（无空指针风险）
//底层实现（编译器）	栈上拷贝实参	         栈上存储指针变量	               通常等价于指针，但语法优化
//适用场景	       小对象、无需修改实参	     需修改实参、允许空值、C 兼容	    需修改实参、大对象 / 类对象、追求简洁安全