# include <iostream>
# include <chrono>  //高精度计时
# include <vector>
# include <random>

using namespace std;
using namespace chrono;


// -------------------------- 1. 传值版本：参数是vector拷贝 --------------------------
// 输入：传值的灰度图img，阈值threshold
// 输出：二值化结果（新vector，不修改原图像）
vector<vector<int>> thresholdSegByValue(vector<vector<int>> img, int threshold){
    vector<vector<int>> result;
    result.resize(img.size());

    for(int i = 0; i < img.size(); ++i){
        result.resize(img[i].size());
        for(int j = 0;j < img[i].size(); ++j){
            result[i][j] = (img[i][j] >= threshold) ? 1 : 0;
        }
    }

    return result;
}





// -------------------------- 2. 传引用版本：参数是const引用 --------------------------
// 输入：const引用的灰度图img（只读，不允许修改原图像），阈值threshold
// 输出：二值化结果（新vector，原图像不变）
vector<vector<int>> thresholdSegByRef(const vector<vector<int>>& img, int threshold){
    vector<vector<int>> result;
    result.resize(img.size());

    for(int i = 0; i < img.size(); ++i){
        result.resize(img[i].size());
        for(int j = 0; j < img[i].size(); ++j){

            result[i][j] = (img[i][j] >= threshold) ? 1 : 0;

        }
    }

    return result;

}










// -------------------------- 辅助函数：生成随机灰度图（模拟实际图像） --------------------------
// 输入：图像宽width、高height，像素值范围[0, 255]
// 输出：随机填充的灰度图
vector<vector<int>> generateRandomGrayImage(int width, int height){
    vector<vector<int>> img(height, vector<int>(width));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,255);

    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            img[i][j] = dis(gen);
        }
    }

    return img;
}






int main(){
    const int IMG_WIDTH = 3000;
    const int IMG_HEIGHT = 3000;
    const int THRESHOLD = 128;


    cout << "生成 " << IMG_WIDTH << "x" << IMG_HEIGHT << " 灰度图..." << endl;
    vector<vector<int>> garyImg = generateRandomGrayImage(IMG_WIDTH, IMG_HEIGHT);
    cout << "图像生成完成！" << endl << endl;


    cout << "=== 测试传值版本 ===" << endl;
    auto startValue = high_resolution_clock::now();
    vector<vector<int>> resultValue = thresholdSegByValue(garyImg, THRESHOLD);
    auto endValue = high_resolution_clock::now();
    auto durationValue = duration_cast<milliseconds>(endValue - startValue).count();
    cout << "传值版本耗时：" << durationValue << " 毫秒" << endl << endl;


    cout << "=== 测试传引用版本 ===" << endl;
    auto startRef = high_resolution_clock::now();
    vector<vector<int>> resultRef = thresholdSegByRef(garyImg, THRESHOLD);
    auto endRef = high_resolution_clock::now();
    auto durationRef = duration_cast<milliseconds>(endRef - startRef).count();
    cout << "传值版本耗时：" << durationRef << " 毫秒" << endl << endl;

    bool isResultSame = true;
    for (int i = 0; i < IMG_WIDTH && isResultSame; ++i){
        for(int j = 0; j < IMG_HEIGHT && isResultSame; ++j){
            if(resultValue[i][j] != resultRef[i][j]){
                isResultSame = false;
            }
        }
    }


    cout << "两种方式结果是否一致？" << (isResultSame ? "是" : "否") << endl;

    return 0;



}