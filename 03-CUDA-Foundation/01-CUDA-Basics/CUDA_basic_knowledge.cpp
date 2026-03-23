


//////////////////////////////////////////////////////////// 【CUDA 两大基础知识】 ////////////////////////////////////////////////////////////
// 线程层次
// 存储模型



///////////////////////////////////////////////// 【【线程层次】】 /////////////////////////////////////////////////

// 线程 thread
// 线程块 block
// 网格 grid 对应kernel函数



//////////////////////////////////////// thread ////////////////////////////////////////
// SPMD （single program mutltiple data）单程序多数据流 
//////////////////////////////////////// block /////////////////////////////////////////
// 每个线程块内线程数相同
// 块内线程数量有限，A100最多1024个线程
// 线程块以任意顺序执行，之间不能通信
// 块内线程通信： shared memory， 线程可以同步__syncthreads()
////////////////////////////////////////// grid ////////////////////////////////////////
// 每个线程块都有编号
// 一个kernel函数到一个grid，由grid里所有线程执行、
// 网格内所有线程共享全局存储器 global memory
////////////////////////////////////////// wrap ////////////////////////////////////////
// 线程束，32个线程构成，SM中调度和运行的基本单位

//////////////////////////////////////// 硬件映射 //////////////////////////////////////
// 实际调用的block数量往往大于实际SM数量， Automic Scalability性
// 一个SM可处理多个block
// 每个block都可以在GPU任何可用的SM上调度
// 一个CUDA程序可以在不同的GPU机器上运行，即使算力不同


kernelFunc<<<gridsize,blocksize>>>(param1, param2);
// gridsize: grid中block布局
// blocksize：block中thread布局
// dim3
// 线程总数=线程块数*块内线程数

//dim3 CUDA 内置数据结构
dim3 A(x,y,z);
// 代表三个维度大小
// 至少指定x，其他维度不指定则默认1

dim3 gridsize(3,2);
dim3 blocksize(4,3);
func<<<gridsize, blocksize>>>(...);



threadIdx.[x,y,z];
blockIdx.[x,y,z];
blockDim.[x,y,z]; //block的尺寸
gridDim.[x,y,z]; //grid的尺寸
//总线程数
gridDim.x*gridDim.y*gridDim.z*blockDim.x*blockDim.y*blockDim.z;


// 一维grid，一维block，线程块内线程数量有限，向量长度受限
// 改成多个block计算
__global__ void vecAdd(int *A, int B*, int *C, int width)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if(id < width)
       C[id] = A[id] + B[id];
}

int blocksize = 32;
vecAdd<<<(width + blocksize - 1)/blocksize, blocksize>>>(A, B, C, width);

// 二维grid，二维block
__global__ void matAdd(float *A, float B*, float *C, int N)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int id = row * N + col;
    if(row < N && col < N)
       C[id] = A[id] + B[id];
}

dim3 blocksize(32,32);
dim3 gridsize((N+32-1)/32, (N+32-1)/32);
vecAdd<<<gridsize, blocksize>>>(A, B, C, width);

// 三维block计算 
int threadId = threadIdx.z * blockDim.x * blockDim.y + threadIdx.y * blockDim.x + threadIdx.x;





///////////////////////////////////////////////// 【【存储模型】】 /////////////////////////////////////////////////

 
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




//CUDA核心（流处理器）（SP）(SM)：决定CUDA运算的并行运算吞吐量上限
//GPU 核心主频（shared clock）：决定CUDA运算的指令执行速度与延迟
//显存带宽：决定CUDA运算的数据供给上限，常见性能瓶颈


//计算密集型  CUDA核心数>主频>带宽
//访存密集型  带宽>CUDA核心数>主频
//延迟敏感性  主频>CUDA核心数>带宽



/* 
              executed    callable
__device__     device      device
__global__     device      host
__host__       host        host
 */


//  标准C函数       CUDA C函数        功能    
//   malloc        cudaMalloc       内存分配
//   memcpy        cudaMemcpy       内存复制（cudaMemcpyHostToHost）
//   free          cudaFree         内存释放

// cudaError_t类型， 记录CUDA错误