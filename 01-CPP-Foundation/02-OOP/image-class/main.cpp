# include "Image.h"
#include <iostream>
using namespace std;


// ==================== 【重点：浅拷贝错误演示】 ====================
// 注释掉 类中的 拷贝构造函数，就会触发浅拷贝！
// 浅拷贝后果：两个对象指向同一块内存，析构时重复释放 → 程序崩溃！
void shallowCopyDemo(){
    cout << "\n===== 浅拷贝演示（会崩溃！）=====\n";
    Image a(100, 100);
    Image b = a;  // 编译器自动生成浅拷贝

    a.showInfo();
    b.showInfo();  // 地址和 a 完全一样！

    // 函数结束，a 和 b 先后析构，同一块内存 delete[] 两次 → 崩溃,解决方案就是第一次delete[]后，将其置为nullptr
}

// ==================== 深拷贝正常运行 ====================
void deepCopyTest() {
    cout << "\n===== 深拷贝测试（安全）=====\n";
    Image img1(200, 100);
    img1.fill(255);

    Image img2 = img1;  // 调用深拷贝
    img1.setPixel(0, 0, 100);

    cout << "img1(0,0): " << (int)img1.getPixel(0, 0) << "\n";
    cout << "img2(0,0): " << (int)img2.getPixel(0, 0) << "\n";
    // 互相不影响 → 深拷贝成功
}


// ==================== 栈对象 & 堆对象 ====================
void stackVsHeapTest() {
    cout << "\n===== 栈对象 vs 堆对象 =====\n";
    Image stackImg(50, 50);       // 栈：自动释放
    Image* heapImg = new Image(300, 200); // 堆：手动释放

    heapImg->showInfo();
    delete heapImg;  // 必须手动 delete
}


// ==================== main ====================
int main(){
    // 浅拷贝演示（打开注释就能看到崩溃，证明浅拷贝错误！）
    // shallowCopyDemo();


    // 深拷贝测试（正常运行）
    deepCopyTest();

    // 栈 vs 堆
    stackVsHeapTest();

    cout << "\n===== 程序正常结束 =====\n";
    return 0;
}