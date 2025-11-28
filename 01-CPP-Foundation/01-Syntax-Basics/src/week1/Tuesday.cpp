// ┌─────────────┐      ┌─────────────┐      ┌─────────────┐     ┌─────────────┐
//   你的源码     │ → → │CMakeLists.txt│  → → │ 构建脚本    │ → →  │ 可执行文件  │
// │ （.cpp/.h） │      │ （跨平台配置）│      │ （Makefile/ │      │ （.exe）    │
// └─────────────┘      └─────────────┘      │  VS.sln）   │     └─────────────┘
//                                           └──────┬──────┘
//                                                  ↓
//                                           ┌─────────────┐
//                                           │ 编译器/链接器 │
//                                           │ （g++/MSVC） │
//                                           └─────────────┘
//                                                  ↑
//                                           ┌─────────────┐
//                                           │ 依赖库       │
//                                           │ （DCMTK/NII）│
//                                           └─────────────┘


//
//
//
//
//
//

//指针操作

//取地址符 &：获取变量的内存地址（如 &a 表示变量 a 的地址）。
//解引用符 *：通过指针存储的地址，访问目标变量的值（如 *p 表示指针 p 指向的变量）。

# include<iostream>
using namespace std;

int main(){
    int a =20;
    int* p = &a;
    std::cout << a << std::endl;
    std::cout << &a << std::endl;
    std::cout << p << std::endl; 
    std::cout << *p << std::endl; 

    *p = 20;
    std::cout << a <<std::endl;

    return 0;
}






//空指针 nullptr 空指针是指向 “无效地址” 的指针，用于表示指针未指向任何合法变量（避免野指针）
//特性：不能解引用空指针（会触发程序崩溃，属于未定义行为）；可用于判断指针是否有效。

int* p1 = nullptr;  // 正确：空指针（C++11推荐）
// int* p3 = 0;      // 不推荐，0是整数，非严格空指针

/* if (p1 == nullptr) { // 判断指针是否为空
    cout << "p1是空指针，不能解引用" << endl;
} */
// *p1 = 30; // 错误：解引用空指针，程序崩溃














//指针算术、数组与指针的关系

//指针算术: 指针算术的目的是 “指向相邻的同类型变量”，而非修改地址数值
#include <iostream>
using namespace std;

int main() {
    int arr[] = {10, 20, 30};
    int* p = arr;          // p指向arr[0]（地址假设为0x0012FF30）
    
    p++;                   // int占4字节，p偏移4字节，指向arr[1]（地址0x0012FF34）
    cout << *p << endl;    // 输出20
    
    p += 1;                // 再偏移4字节，指向arr[2]（地址0x0012FF38）
    cout << *p << endl;    // 输出30
    
    char* cp = (char*)arr; // 强制转换为char*（1字节）
    cp++;                  // 偏移1字节，指向arr[0]的第二个字节（地址0x0012FF31）
    return 0;
}

//数组名的本质是数组首元素的常量地址（不可修改），因此数组与指针在很多场景下可等价使用：
//arr[i] 等价于 *(arr + i)（通过地址偏移访问元素）；
//数组名不能自增 / 自减（如 arr++ 错误），但指针变量可以（如 p++ 正确）
int arr[] = {1, 2, 3};
int* p = arr; // 等价于 int* p = &arr[0]

/* cout << arr[1] << endl;   // 输出2
cout << *(arr + 1) << endl;// 输出2（数组名做地址偏移）
cout << p[1] << endl;     // 输出2（指针模拟数组访问）
cout << *(p + 1) << endl; // 输出2（指针偏移） */

// arr++; // 错误：数组名是常量地址，不能修改
//p++; // 正确：指针变量可修改













//指针数组 vs 数组指针（对比区别）
//本质不同（数组 vs 指针），关键看 [] 和 * 的优先级（[] 优先级高于 *，需用括号改变优先级）


/* 指针数组：“数组，元素是指针”
定义：类型* 数组名[数组长度]（如 int* arr[5]）；
本质：数组，每个元素都是一个指针（存储地址）；
内存：数组大小 = 数组长度 × 指针字节数（64 位系统中每个指针 8 字节） */

#include <iostream>
using namespace std;

int main() {
    int a = 10, b = 20, c = 30;
    int* ptrArr[3] = {&a, &b, &c}; // 指针数组：3个元素，每个是int*
    
    // 访问：先取数组元素（指针），再解引用
    cout << *ptrArr[0] << endl; // 输出10（ptrArr[0]是&a，*ptrArr[0]是a的值）
    cout << *ptrArr[1] << endl; // 输出20
    
    return 0;
}


/* 数组指针：“指针，指向数组”
定义：类型 (*指针名)[数组长度]（如 int (*p)[5]）；
本质：指针，专门指向 “固定长度的数组”；
步长：指针 p++ 时，偏移量 = 数组长度 × 元素类型字节数（如指向 int[3] 的指针，步长是 3×4=12 字节） */

int main() {
    int arr[2][3] = {{1,2,3}, {4,5,6}};
    int (*arrPtr)[3] = arr; // 数组指针：指向int[3]类型的数组（arr是第一行的地址）
    
    cout << (*arrPtr)[0] << endl; // 输出1（arrPtr指向第一行，*arrPtr是第一行数组，[0]取第一个元素）
    arrPtr++; // 偏移12字节（3×4），指向第二行
    cout << (*arrPtr)[0] << endl; // 输出4
    
    return 0;
}





















//多维数组、指针访问
//C/C++ 中没有真正的 “多维数组”，多维数组是一维数组的嵌套（如二维数组是 “元素为一维数组的一维数组”），内存中按 “行优先” 连续存储。

#include <iostream>
using namespace std;

int main() {
    int a[2][3] = {{1,2,3}, {4,5,6}};
    
    // 方式1：数组名直接访问（最直观）
    cout << a[1][2] << endl; // 输出6
    
    // 方式2：数组指针访问（匹配数组名类型）
    int (*p)[3] = a;
    cout << (*(p + 1))[2] << endl; // 输出6（p+1指向第二行，*(p+1)是第二行数组）
    
    // 方式3：普通指针访问（强制转换为int*）
    int* q = (int*)a; // 二维数组首地址等价于一维数组首地址
    cout << *(q + 1*3 + 2) << endl; // 输出6（偏移量=行号×列数 + 列号）
    
    return 0;
}


//多维数组传递给函数
//函数参数中，多维数组的第一维可以省略，但第二维及以后必须明确（因为编译器需要计算行偏移）：
//正确声明：void printArr(int arr[][3], int row) 或 void printArr(int (*arr)[3], int row)（数组指针形式）；
//错误声明：void printArr(int arr[][], int row)（未指定第二维，无法计算偏移）

void printArr(int (*arr)[3], int row) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < 3; j++) {
            cout << *(*(arr + i) + j) << " ";
        }
        cout << endl;
    }
}

int main() {
    int a[2][3] = {{1,2,3}, {4,5,6}};
    printArr(a, 2); // 传递数组名（数组指针类型）
    return 0;
}
          



















//C 风格字符串、str 系列函数

//常用 str 系列函数（需包含 <cstring> 头文件）
//函数名	                                      功能	                                      示例	                        注意事项
//strlen(const char* s)	                         计算字符串长度（不含 '\0'）	               strlen("abc") → 3	         若字符串无 '\0'，会越界查找
//strcpy(char* dest, const char* src)	         复制 src 到 dest（含 '\0'）	              strcpy(dest, "abc")	        dest 必须有足够空间，否则缓冲区溢出
//strcat(char* dest, const char* src)	         拼接 src 到 dest 末尾	                      strcat(dest, "def")	        dest 需足够大，且本身是合法字符串（含 '\0'）
//strcmp(const char* s1, const char* s2)	     比较字符串：相等返回 0，s1>s2 返回正，否则负	strcmp("abc", "abd") → -1	  比较 ASCII 码，而非长度；不能用 == 替代

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str1[20] = "hello";
    char str2[20] = "world";
    
    cout << "str1长度：" << strlen(str1) << endl; // 输出5（不含'\0'）
    cout << "str1数组大小：" << sizeof(str1) << endl; // 输出20（数组实际大小）
    
    strcat(str1, " ");
    strcat(str1, str2); // 拼接后str1 = "hello world"
    cout << "拼接结果：" << str1 << endl;
    
    if (strcmp(str1, "hello world") == 0) { // 用strcmp比较内容
        cout << "字符串相等" << endl;
    }
    
    return 0;
}


/* 易错点	错误示例	原因分析	避免方法
字符串缺少 '\0' 终止符	char str[] = {'a','b','c'}; cout << strlen(str);	strlen 会一直查找 '\0'，导致越界，返回随机值	手动添加 '\0'（如 char str[] = {'a','b','c','\0'}）或用字符串常量初始化（自动加 '\0'）
strcpy/strcat 缓冲区溢出	char str[3]; strcpy(str, "abc");	"abc" 含 '\0' 共 4 字节，str 仅 3 字节，覆盖其他内存	确保目标数组大小 ≥ 源字符串长度 + 1（预留 '\0' 空间），或用 strncpy/strncat（指定最大拷贝长度）
用 == 比较字符串内容	if (str1 == str2)	== 比较的是字符串首地址（是否指向同一内存），而非内容	必须用 strcmp 函数（strcmp(str1, str2) == 0 表示内容相等）
操作空指针	strlen(nullptr);	str 系列函数要求参数是合法字符串首地址，空指针会导致崩溃	调用前判断指针是否为 nullptr，且字符串是否合法（含 '\0'）
字符串常量不可修改	char* str = "abc"; str[0] = 'A';	字符串常量存储在只读内存区，修改会触发内存错误	若需修改，用字符数组初始化（char str[] = "abc"） */



























//常量指针与指针常量（const 位置差异）

//核心规则：const 修饰的是 “其右边最近的内容”（口诀：左定值，右定向）：
//左定值：const 在 * 左边 → 修饰指针指向的 “内容”，内容不可改（常量指针）；
//右定向：const 在 * 右边 → 修饰指针 “本身”，指针不可改（指针常量）。

//常量指针（const int* p /int const* p）
//定义：const int* p 或 int const* p（两者等价）；
//特性：指针指向的内容不可修改，但指针本身可以指向其他变量
int a = 10, b = 20;
const int* p = &a; // 常量指针

// *p = 30; // 错误：指向的内容不可改
a = 30; // 正确：变量a本身可改（const仅限制指针访问）
p = &b; // 正确：指针本身可以指向其他变量
cout << *p << endl; // 输出20




//指针常量（int* const p）
//定义：int* const p；
//特性：指针本身不可修改（不能指向其他变量），但指向的内容可以修改
int a = 10, b = 20;
int* const p = &a; // 指针常量（必须初始化，否则无法修改指针）

*p = 30; // 正确：指向的内容可改
cout << a << endl; // 输出30
// p = &b; // 错误：指针本身不可改


//const 指针常量（const int* const p）
//定义：const int* const p；
//特性：指针本身不可改，指向的内容也不可改（最严格的限制）
int a = 10, b = 20;
const int* const p = &a; // 必须初始化

// *p = 30; // 错误：内容不可改
// p = &b; // 错误：指针不可改
a = 30; // 正确：变量a本身可改
cout << *p << endl; // 输出30

























//指针与函数（函数指针基础）

//函数指针的本质：指向函数入口地址的指针
//函数在内存中会占用一段连续空间，其入口地址（函数名）可被指针存储，该指针即为函数指针。

//函数指针的定义与语法
//语法：返回类型 (*指针名)(参数类型列表)
//括号必须加：(*指针名) 确保是指针，而非返回指针的函数（如 int* p(int) 是返回 int* 的函数）；
//参数类型列表必须与目标函数完全一致（参数个数、类型、顺序）；
//返回类型必须与目标函数一致

#include <iostream>
using namespace std;

// 目标函数：两数相加
int add(int x, int y) {
    return x + y;
}

// 目标函数：两数相乘
int multiply(int x, int y) {
    return x * y;
}

int main() {
    // 定义函数指针p，指向返回int、参数为(int,int)的函数
    int (*pFunc)(int, int) = add; // 函数名add是入口地址，无需&
    
    // 调用方式1：指针直接调用（推荐）
    cout << pFunc(2, 3) << endl; // 输出5
    
    // 调用方式2：解引用后调用（等价）
    cout << (*pFunc)(2, 3) << endl; // 输出5
    
    // 函数指针切换指向的函数
    pFunc = multiply;
    cout << pFunc(2, 3) << endl; // 输出6
    
    return 0;
}



//函数指针作为函数参数（回调函数基础）
//函数指针可作为参数传递给其他函数，让被调用函数 “回调” 指定函数，实现灵活扩展
// 计算器函数：接收两个数和一个运算函数指针
void calculate(int a, int b, int (*op)(int, int)) {
    cout << "结果：" << op(a, b) << endl;
}

int main() {
    calculate(2, 3, add);      // 回调add，输出5
    calculate(2, 3, multiply); // 回调multiply，输出6
    return 0;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////易错点集中在：未初始化指针、类型不匹配、边界越界、const 位置混淆
////////////////////////////////////////////////////////////////////////////////////////////////////////