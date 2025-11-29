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
void initMatrix(int row, int col, int* mat, bool isRandom) {
    if (mat == nullptr || row <= 0 || col <= 0) {
        cout << "矩阵初始化失败：参数无效！" << endl;
        return;
    }

    cout << "初始化 " << row << "x" << col << " 矩阵：" << endl;
    if (isRandom) {
        // 随机生成1-10的整数（需包含<cstdlib>）
        srand((unsigned int)time(nullptr));  // 随机数种子（仅需初始化一次）
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // 指针访问：*(mat + i*col + j) 等价于 mat[i][j]
                *(mat + i * col + j) = rand() % 10 + 1;  // 1-10
            }
        }
    } else {
        // 手动输入矩阵元素
        for (int i = 0; i < row; i++) {
            cout << "请输入第 " << i + 1 << " 行（共" << col << "个数字，空格分隔）：";
            for (int j = 0; j < col; j++) {
                cin >> *(mat + i * col + j);  // 指针访问，存储输入值
            }
        }
    }
}





// 打印矩阵：格式化输出，元素右对齐（美观易读）
void printMatrix(int row, int col, const int* mat) {
    if (mat == nullptr || row <= 0 || col <= 0) {
        cout << "矩阵打印失败：参数无效！" << endl;
        return;
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // 指针访问元素，setw(4) 控制每个元素占4个字符宽度（右对齐）
            cout << setw(4) << *(mat + i * col + j);
        }
        cout << endl;  // 每行结束换行
    }
}



// 核心函数：矩阵加法（任意尺寸）
// 参数：row=行数，col=列数；matA、matB=输入矩阵；matResult=输出结果矩阵
// 返回值：true=加法成功，false=失败（参数无效）
bool matrixAdd(int row, int col, const int* matA, const int* matB, int* matResult) {

    // 1. 参数合法性校验（规避空指针、非法尺寸）
    if (matA == nullptr || matB == nullptr || matResult == nullptr) {
        cout << "错误：输入/输出矩阵指针不能为空！" << endl;
        return false;
    }
    if (row <= 0 || col <= 0) {
        cout << "错误：矩阵行数/列数必须为正整数！" << endl;
        return false;
    }



    // 2. 指针遍历矩阵，逐元素相加（无越界）
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // 关键：二维索引 → 线性地址映射：i*col + j
            // 指针访问：*(mat + 偏移量) = 目标元素
            *(matResult + i * col + j) = *(matA + i * col + j) + *(matB + i * col + j);
        }
    }


    cout << "\n矩阵加法完成！" << endl;
    return true;

}













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







    // -------------------------- 测试3：极端尺寸（1x5矩阵，验证通用性） --------------------------
    cout << "\n\n【测试3：1x5矩阵加法（随机生成）】" << endl;
    row = 1, col = 5;
    int matA1x5[row][col];
    int matB1x5[row][col];
    int matResult1x5[row][col] = {0};

    initMatrix(row, col, (int*)matA1x5, true);
    initMatrix(row, col, (int*)matB1x5, true);

    cout << "\n矩阵A（1x5）：" << endl;
    printMatrix(row, col, (int*)matA1x5);
    cout << "\n矩阵B（1x5）：" << endl;
    printMatrix(row, col, (int*)matB1x5);

    if (matrixAdd(row, col, (int*)matA1x5, (int*)matB1x5, (int*)matResult1x5)) {
        cout << "\nA + B 结果（1x5）：" << endl;
        printMatrix(row, col, (int*)matResult1x5);
    }

    cout << "\n===== 项目结束 =====" << endl;
    return 0;



}