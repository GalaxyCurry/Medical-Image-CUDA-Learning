


__global__ void convolution1D(float *N, int width, float *M, int filterSize)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    float tmpP = 0;
    int startPos = id - (filterSize/2);
    for (int i = 0; i < filterSize; i++)
    {
        int offset = startPos + i;
        if(offset >= 0 && offset < width)
        {
            tmpP += N[offset] * M[i];
        }
    }
    P[id] = tmpP;
    
}

///////////////////////////////////// 影响计算性能的地方？  /////////////////////////////////////
///////////////////////////////////// 1.控制流多样性：分支if  /////////////////////////////////////
///////////////////////////////////// 2.计算/访存比例不高：浮点运算:全局访存=1:1 /////////////////////////////////////
///////////////////////////////////// 3.重复访存：卷积核、输入数据  /////////////////////////////////////



// 使用常量内存与共享内存加速一维卷积算法

// 项目实现步骤
// 1.使用常量内存加速一维卷积算法
// 2.使用常量内存+共享内存加速一维卷积算法
// 3.测试加速效果




// 分析1：卷积核重复访问
//        所有线程都需要访问卷积核
//        不需要修改卷积核（只读）
//        卷积核尺寸小
//        适合放入常量内存

// 首先查看常量内存大小一般64KB
// 定义全局变量，分配常量内存
const int filterSize = 5;
__constant__ float deviceM[filterSize];
// 复制卷积核到常量内存上
cudaMemcpyToSymbol(deviceM, hostM, sizeof(float) * filterSize);

//编写kernel函数使用常量内存
__global__ void convolution1D_kernel(float *N, float *p, int width)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    float tmpP = 0;
    int startPos = id - (filterSize / 2);
    for (int i = 0; i < filterSize; i++)
    {
        int offset = startPos + i;
        if(offset >= 0 && offset < width)
        {
            tmpP += N[offset] * deviceM[i];
        }
    }
    P[id] = tmpP;
}


// 分析2： 输入数据重复访问

// 使用共享内存优化， kernel函数里声明共享内存数组
__shared__ float N_ds[tileSize + filterSize - 1];
// 左侧边缘元素写入共享内存：当前block，最后（卷积核个数/2）个线程加载左侧边缘元素
int radius = filterSize / 2; //一侧边缘元素的个数
if (threadIdx.x >= (blockDim.x - radius))  //如果是最后radius个线程
{
    //当前block的边缘元素实际上就是上一个block末尾线程取的tile元素
    int halo_index_left = (blockIdx.x - 1) * blockDim.x +threadIdx.x;
    if(halo_index_left < 0) //padding的元素，赋值为0
        N_ds[threadIdx.x - (blockDim.x - radius)] = 0;  //共享内存下标等于线程相对于（blockDim.x - radius）的偏移量
    else
        N_ds[threadIdx.x - (blockDim.x - radius)] = N[halo_index_left];   //从全局内存加载
}


// 右侧边缘元素写入共享内存
if (threadIdx.x < radius)  //如果是前radius个线程
{
    //当前block的边缘元素实际上就是下一个block前面线程取的tile元素
    int halo_index_right = (blockIdx.x + 1) * blockDim.x +threadIdx.x;
    if(halo_index_right >= width) //padding的元素，赋值为0
        N_ds[threadIdx.x + blockDim.x + radius] = 0;  //共享内存索引等于线程序号+线程块长度+边缘元素个数
    else
        N_ds[threadIdx.x + blockDim.x + radius] = N[halo_index_right];   //从全局内存加载
}


// 中间元素写入共享内存，每个线程加载对应位置
int id = blockIdx.x * blockDim.x +threadIdx.x;
if(id < width)
    N_ds[threadIdx.x + radius] = N[id];
else
    N_ds[threadIdx.x + radius] = 0;



//在读共享内存之前要同步，保证所有线程都写完
__syncthreads();

//线程块使用的共享内存索引 [threadIdx.x, threadIdx.x + filterSize-1]
float tmpP = 0;
for (int i = 0; i < filterSize; i++)
{
    
    tmpP += N_ds[threadIdx.x + i] * deviceM[i];

}
P[id] = tmpP;

    



