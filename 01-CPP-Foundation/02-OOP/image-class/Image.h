#ifndef IMAGE_H
#define IMAGE_H

class Image{
private:
    int width;
    int height;
    unsigned char* pixels; // 指针：浅拷贝必出问题

public:
    // 构造函数（默认、带参、重载）
    Image();
    Image(int w, int p);
    Image(int size);
    
    //析构函数
    ~Image();

    // 拷贝构造（深拷贝版本）l
    Image(const Image& other);

    //成员函数
    void setPixel(int x, int y, unsigned char val);
    unsigned char getPixel(int x, int y) const;
    void showInfo() const;
    void fill(unsigned char val);

    //this指针
    Image& setWh(int w, int h);

};

//浅拷贝演示函数
void shallowCopyDemo();


#endif