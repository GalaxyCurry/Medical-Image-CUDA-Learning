#include "Image.h"
#include <iostream>
#include <cstring>
using namespace std;



// ==================== 构造函数 ====================
Image::Image():width(1), height(1){
    pixels = new unsigned char[1]();
    cout << "[默认构造] 1x1\n";
}

Image::Image(int w, int h):width(w), height(h){
    int total = w*h;
    pixels = new unsigned char[total];
    memset(pixels, 0 ,total);
    cout << "[带参构造] " << w << "x" << h << "\n"
}

Image::Image(int size):width(size), height(size){
    int total = size*size;
    pixels = new unsigned char[total];
    memset(pixels, 0, total);
    cout << "[重载构造] 正方形" << size << "\n";

}

// ==================== 析构函数 ====================
Image::~Image(){
    if(pixels){
        cout << "[析构] 释放内存\n";
        delete[] pixels;
        pixels = nullptr;
    }
}

// ==================== 拷贝构造（深拷贝） ====================
Image::Image(const Image& other){
    width = other.width;
    height = other.height;
    int total = width * height;

    pixels = new unsigned char[total];
    memcpy(pixels, other.pixels, total);

    cout <<"[拷贝构造-深拷贝] 完成\n";
}


// ==================== 普通成员 ====================

void Image::setPixel(int x, int y, unsigned char val){
    if(x >=0 && x < width && y >=0 && y< height)
       pixels[y * width + x] = val;
}

unsigned char Image::getPixel(int x, int y) const {
    if(x >= 0 && x < width && y >= 0 && y < height)
       return pixels[y*width + x];
    return 0;
}

void Image::showInfo() const {
    cout << "尺寸:" << width << "x" << height
         << " 像素地址:" << (void*)pixels << "\n";
}

void Image::fill(unsigned char val) {
    int total = width * height;
    memset(pixels, val, total);
}


// ==================== this 指针 ====================

Image& Image::setWh(int w,int h){
    this ->width = w;
    this ->height = h;
    return *this;
}