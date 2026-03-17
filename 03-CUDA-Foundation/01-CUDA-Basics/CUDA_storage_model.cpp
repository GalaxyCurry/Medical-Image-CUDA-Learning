

//内存类型              属性         作用域        生命周期
//register          片上，可读写   每个线程专用      线程
//local memory      片外，可读写   每个线程专用      线程
//shared memory     片上，可读写     block共享    块内所有线程
//constant memory   片外，只读       grid共享      应用程序
//global memory     片外，可读写     grid共享      应用程序
//texture memory     片外，只读      grid共享      应用程序



//变量声明                 存储器         作用域       生命周期
//int a                   寄存器          线程          线程
//int a[100000]           本地内存        线程          线程
//__shared__ int a[100]   共享内存        块            块
//__constant__ int a      常量内存        全局          应用程序
//__device__ int a        全局内存        全局          应用程序



// cpu 主存（DRAM） L3   L1/L2   寄存器
// Gpu 显存（DRAM） L2   L1      寄存器
// 容量   大 -> 小
// 速度   慢 -> 快