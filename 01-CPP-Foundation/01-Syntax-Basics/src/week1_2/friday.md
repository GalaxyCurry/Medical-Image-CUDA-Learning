// 引用需要初始化且不能为空；指针可以延迟初始化，可以设为空指针
//指针可以重新指向；引用不能重新绑定


#include <iostream>
using namespace std;

int main() {
    // ====== 初始化对比 ======
    int a = 10;
    int* ptr;       // 指针可以延迟初始化
    ptr = &a;       // 现在指向a
    ptr = nullptr;  // 可以设为空指针

   int& ref = a;   // 引用必须初始化且不能为空
   // int& ref2;    // 错误：引用必须初始化
   // int& ref3 = nullptr; // 错误：不能绑定到空

   // ====== 重新绑定对比 ======
   int b = 20;
   ptr = &b;       // 指针可以重新指向b
   // &ref = b;     // 错误：引用不能重新绑定

   // ====== 内存占用对比 ======
   cout << "指针大小: " << sizeof(ptr) << " bytes" << endl; // 4或8字节
   cout << "引用大小: " << sizeof(ref) << " bytes" << endl;  // 显示a的大小

   // ====== 操作方式对比 ======
   *ptr = 30;      // 指针需要解引用
   ref = 40;       // 引用直接操作

    // ====== 安全性对比 ======
   if(ptr != nullptr) {  // 使用指针需要判空（行29）
       cout << *ptr << endl;
   }
   cout << ref << endl;  // 引用无需判空检查（行32）

   // ====== 动态内存管理 ======
   int* dynPtr = new int(50);  // 指针用于动态内存
   cout << *dynPtr << endl;
   delete dynPtr;              // 必须手动释放
   // 引用不能用于动态内存管理

   // ====== 函数参数传递 ======
   auto modifyByPtr = [](int* p) { if(p) *p += 1; };
   auto modifyByRef = [](int& r) { r += 1; };
   
   modifyByPtr(&a);
   modifyByRef(a);
   cout << "a = " << a << endl;  // 输出42

   //====== const的修饰 ======
   // 引用示例    
   const int ci = 10;  
   //int& r = ci;  // 错误：非const引用不能绑定到const对象
   const int& cr = ci;  //正确：const引用可以绑定到const对象
    //指针示例
   int a = 10;
   const int* p1 = &a;  // p1指向的值是const的
   //*p1 = 20;  //错误：不能通过p1修改a的值
   int* const p2 = &a;  // p2本身是const的，不能改变指向
   //p2 = &b;  //错误：不能改变p2指向的对象

   return 0;
}


![alt text](image.png)