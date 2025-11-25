# include <iostream>
using namespace std;


int main(){

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