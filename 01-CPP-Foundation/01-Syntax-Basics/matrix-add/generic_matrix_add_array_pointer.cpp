#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
using namespace std;

// 常量定义（3x3默认尺寸）
const int DEFAULT_ROW = 3;
const int DEFAULT_COL = 3;

// -------------------------- 功能函数声明 --------------------------
void initMatrix(int row, int col, int* mat, bool isRandom = false);
void printMatrix(int row, int col, const int* mat);
bool matrixAdd(int row, int col, const int* matA, const int* matB, int* matResult);

// -------------------------- 功能函数实现 --------------------------
// 初始化矩阵：数组指针访问元素
void initMatrix(int row, int col, int* mat, bool isRandom) {
    if (mat == nullptr || row <= 0 || col <= 0) {
        cout << "矩阵初始化失败：参数无效！" << endl;
        return;
    }

    // 关键：定义数组指针，指向「col列的int数组」（匹配矩阵每行的类型）
    int (*pMat)[col] = (int (*)[col])mat; // 强制转换为数组指针

    cout << "初始化 " << row << "x" << col << " 矩阵：" << endl;
    if (isRandom) {
        srand((unsigned int)time(nullptr));
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // 数组指针访问：(*(pMat + i)) 等价于第i行数组，再取[j]列元素
                (*(pMat + i))[j] = rand() % 10 + 1; // 1-10随机数
            }
        }
    } else {
        for (int i = 0; i < row; i++) {
            cout << "请输入第 " << i + 1 << " 行（共" << col << "个数字，空格分隔）：";
            for (int j = 0; j < col; j++) {
                cin >> (*(pMat + i))[j]; // 数组指针存储输入值
            }
        }
    }
}

// 打印矩阵：数组指针访问元素（格式化输出）
void printMatrix(int row, int col, const int* mat) {
    if (mat == nullptr || row <= 0 || col <= 0) {
        cout << "矩阵打印失败：参数无效！" << endl;
        return;
    }

    // 常量数组指针（指向const int[col]，避免修改原矩阵）
    const int (*pMat)[col] = (const int (*)[col])mat;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // 数组指针访问：简洁写法 → pMat[i][j]（等价于 (*(pMat+i))[j]）
            cout << setw(4) << pMat[i][j];
        }
        cout << endl;
    }
}

// 核心函数：矩阵加法（数组指针实现，任意尺寸支持）
bool matrixAdd(int row, int col, const int* matA, const int* matB, int* matResult) {
    // 1. 参数合法性校验
    if (matA == nullptr || matB == nullptr || matResult == nullptr) {
        cout << "错误：输入/输出矩阵指针不能为空！" << endl;
        return false;
    }
    if (row <= 0 || col <= 0) {
        cout << "错误：矩阵行数/列数必须为正整数！" << endl;
        return false;
    }

    // 2. 定义数组指针（匹配矩阵每行类型：int[col]）
    const int (*pA)[col] = (const int (*)[col])matA; // 源矩阵A（只读）
    const int (*pB)[col] = (const int (*)[col])matB; // 源矩阵B（只读）
    int (*pResult)[col] = (int (*)[col])matResult;   // 结果矩阵（可写）

    // 3. 数组指针遍历：按行偏移，逐元素相加
    for (int i = 0; i < row; i++) { // i：行索引（pA+i 指向第i行）
        for (int j = 0; j < col; j++) { // j：列索引
            // 核心逻辑：数组指针访问 → 行优先，贴合多维数组存储本质
            pResult[i][j] = pA[i][j] + pB[i][j]; 
            // 等价写法（更直观体现数组指针解引用）：(*(pResult + i))[j] = (*(pA + i))[j] + (*(pB + i))[j];
        }
    }

    cout << "\n矩阵加法完成！" << endl;
    return true;
}

// -------------------------- 主函数（测试逻辑） --------------------------
int main() {
    cout << "===== 数组指针实现矩阵加法 =====" << endl;

    // -------------------------- 测试1：3x3矩阵（手动输入） --------------------------
    cout << "\n【测试1：3x3矩阵加法（手动输入）】" << endl;
    int matA3x3[DEFAULT_ROW][DEFAULT_COL];
    int matB3x3[DEFAULT_ROW][DEFAULT_COL];
    int matResult3x3[DEFAULT_ROW][DEFAULT_COL] = {0};

    initMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matA3x3, false);
    initMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matB3x3, false);

    cout << "\n矩阵A（3x3）：" << endl;
    printMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matA3x3);
    cout << "\n矩阵B（3x3）：" << endl;
    printMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matB3x3);

    if (matrixAdd(DEFAULT_ROW, DEFAULT_COL, (int*)matA3x3, (int*)matB3x3, (int*)matResult3x3)) {
        cout << "\nA + B 结果（3x3）：" << endl;
        printMatrix(DEFAULT_ROW, DEFAULT_COL, (int*)matResult3x3);
    }

    // -------------------------- 测试2：4x2矩阵（随机生成） --------------------------
    cout << "\n\n【测试2：4x2矩阵加法（随机生成）】" << endl;
    int row = 4, col = 2;
    int matA4x2[row][col];
    int matB4x2[row][col];
    int matResult4x2[row][col] = {0};

    initMatrix(row, col, (int*)matA4x2, true);
    initMatrix(row, col, (int*)matB4x2, true);

    cout << "\n矩阵A（4x2）：" << endl;
    printMatrix(row, col, (int*)matA4x2);
    cout << "\n矩阵B（4x2）：" << endl;
    printMatrix(row, col, (int*)matB4x2);

    if (matrixAdd(row, col, (int*)matA4x2, (int*)matB4x2, (int*)matResult4x2)) {
        cout << "\nA + B 结果（4x2）：" << endl;
        printMatrix(row, col, (int*)matResult4x2);
    }

    // -------------------------- 测试3：1x5矩阵（极端尺寸） --------------------------
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