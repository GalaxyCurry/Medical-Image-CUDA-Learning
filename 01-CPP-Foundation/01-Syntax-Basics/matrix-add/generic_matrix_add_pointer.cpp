#include <iostream>
#include <cstdlib>  // 用于随机数（可选）
#include <iomanip>  // 用于格式化输出（矩阵对齐）

using namespace std;


const int DEFAULT_ROW = 3;
const int DEFAULT_COL = 3;


// -------------------------- 功能函数声明 --------------------------
// 1. 初始化矩阵（支持手动输入或随机生成）
void initMatrix(int row, int col, int* mat, bool isRandom = false);

// 2. 打印矩阵（格式化输出，便于查看）
void printMatrix(int row, int col, const int* mat);

// 3. 核心函数：矩阵加法（支持任意尺寸，指针访问元素）
bool matrixAdd(int row, int col, const int* matA, const int* matB, int* matResult);






// -------------------------- 功能函数实现 --------------------------
// 初始化矩阵：isRandom=true→随机生成(1-10)，false→手动输入














// -------------------------- 主函数（测试逻辑） --------------------------
int main(){
    std::cout << "===== 矩阵加法实践项目 =====" << endl;

    // -------------------------- 测试1：默认3x3矩阵（手动输入） --------------------------
    std::cout << "\n【测试1：3x3矩阵加法（手动输入）】" << endl;
    int matA3x3[DEFAULT_ROW][DEFAULT_COL];
    int matB3x3[DEFAULT_ROW][DEFAULT_COL];
    int matResult3x3[DEFAULT_ROW][DEFAULT_COL] = {0};  // 结果矩阵初始化（避免野值）

    // 初始化两个3x3矩阵（手动输入）
    initMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matA3x3, false);
    initMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matB3x3, false);

    // 打印输入矩阵
    cout << "\n矩阵A（3x3）：" << endl;
    printMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matA3x3);
    cout << "\n矩阵B（3x3）：" << endl;
    printMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matB3x3);
    // 矩阵加法（核心调用）
    if(matrixAdd(DEFAULT_ROW, DEFAULT_COL, (int*)matA3x3, (int*)matB3x3, (int*)matResult3x3)){
        std::cout << "\nA + B 结果（3x3）：" << endl;
        printMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matResult3x3);
    }






    // -------------------------- 测试2：任意尺寸矩阵（随机生成，验证灵活性） --------------------------
    cout << "\n\n【测试2：4x2矩阵加法（随机生成）】" << endl;
    int row = 4, col = 2;  // 自定义尺寸（可修改为任意正整数）
    int matA4x2[row][col];  // 变长数组（C++11及以上支持，或用动态内存）
    int matB4x2[row][col];
    int matResult4x2[row][col] = {0};


    // 初始化两个4x2矩阵（随机生成1-10的数）
    initMatrix(row, col, (int*)matA4x2, true);
    initMatrix(row, col, (int*)matB4x2, true);

    // 打印输入矩阵
    cout << "\n矩阵A（4x2）：" << endl;
    printMatrix(row, col, (int*)matA4x2);
    cout << "\n矩阵B（4x2）：" << endl;
    printMatrix(row, col, (int*)matB4x2);

    // 矩阵加法
    if (matrixAdd(row, col, (int*)matA4x2, (int*)matB4x2, (int*)matResult4x2)) {
        cout << "\nA + B 结果（4x2）：" << endl;
        printMatrix(row, col, (int*)matResult4x2);
    }



}