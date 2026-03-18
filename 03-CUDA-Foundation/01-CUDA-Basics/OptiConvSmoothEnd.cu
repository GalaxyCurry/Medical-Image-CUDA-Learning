/* 
CUDA编程实现，使用常量内存加速一维卷积平滑滤波计算，并与原始版本进行性能对比
 */


# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

// 定义卷积核长度以及申请常量内存
/* const int filterSize = 7;
__constant__ float deviceM[filterSize]; */

//从文件读入滤波前数据，作为输入数据
void readInputFile(float *in, int size)
{
    FILE *fp = fopen("noise.txt", "r");
    if (fp == NULL)
    {
        printf("open file failed!\n");
        exit(1);
    }
    for(int i=0; i < size; i++)
    {
        fscanf(fp, "%f", &in[i]);
    }
    fclose(fp);
    printf("read file success!\n");
}

//将滤波后数据写入文件
void writeOutputFile(float *out, int size)
{
    FILE *fp = fopen("conv_result.txt", "w");
    if (fp == NULL)
    {
        printf("open file failed!\n");
        exit(1);
    }
    for(int i=0; i < size; i++)
    {
        fprintf(fp, "%f\n", out[i]);
    }
    fclose(fp);
    printf("write file success!\n");
}


//CPU时间，用于串行实现计时
double cpuSecond()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.e-6);

}


//一维卷积串行实现
void convolution1D_host(float *N, float *P, int width, float *M, int filterSize)
{
    for(int i = 0; i < width; i++)
    {
        float tmpP = 0;
        int startPos = i - (filterSize / 2);

        for(int j = 0; j < filterSize; j++)
        {
            int offset = startPos + j;
            if(offset >= 0 && offset < width)
            {
                tmpP += N[offset] * M[j];
            }
        }
        P[i] = tmpP;
    }
}

//重点：CUDA实现一维卷积，kernel函数
__global__ void convolution1D_kernel(float *N, float *P, int width, float *M, int filterSize)
{
     int id = blockIdx.x * blockDim.x + threadIdx.x;
     float tmpP = 0;
     int startPos = id - (filterSize / 2);
     for(int i = 0; i < filterSize; i++)
     {
        int offset = startPos + i;
        if(offset >= 0 && offset < width)
        {
            tmpP += N[offset] * M[i]
        }
     }
     P[id] = tmpP;

}



int main()
{
    //1.指定输入输出数组大小、卷积核大小， host端申请输入数组、卷积核、输出数组内存空间
    int width = 10000000;
    int filterSize = 7;
    float *hostN = (float *)malloc(sizeof(float) * width);
    float *hostM = (float *)malloc(sizeof(float) * filterSize);
    float *hostP = (float *)malloc(sizeof(float) * width);
    float *hostCPUTest = (float *)malloc(sizeof(float) * width);

    //2.CPU上的输入数据准备，从噪声数据文件读取输入数组，卷积核初始化为平滑滤波
    readInputFile(hostN ,width);
    for(int i = 0; i < filterSize; i++)
    {
        hostM[i] = 1.0 / (float)filterSize;
    }

    //3.串行计算一维卷积，并计时
    double cpuStart = cpuSecond();
    convolution1D_host(hostN, hostCPUTest, width, hostM, filterSize);
    double cpuTime = (cpuSecond() - cpuStart) * 1000;
    printf("CPU,Serial convolution calculation time:  %f ms\n", cpuTime);

    //4.device端申请输入数据、卷积核、输出数组的内存空间
    float *deviceN, *deviceM, *deviceP;
    cudaMalloc((void **)&deviceN, sizeof(float) * width);
    cudaMalloc((void **)&deviceM, sizeof(float) * filterSize);
    cudaMalloc((void **)&deviceP, sizeof(float) * width);

    //5.将输入数组和卷积核从host拷贝到device
    cudaMemcpy(deviceN, hostN, sizeof(float) * width, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceM, hostM, sizeof(float) * filterSize, cudaMemcpyHostToDevice);

    //6.设置网格和线程块的维度和尺寸
    int blockSize = 512;
    dim3 dimBlock(blockSize, 1, 1);
    dim3 dimGrid((width + blockSize -1)/blockSize, 1 ,1);
    
    //7.开始CUDA计时
    cudaEvent_t start,stop;
    float gpuTime = 0.0;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);


    //8.调用kernel函数
    convolution1D_kernel<<<dimGrid, dimBlock>>>(deviceN, deviceP, width, deviceM, filterSize);

    //9.计时结束，计算加速效果
    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpuTime, start, stop);
    
    printf("GPU,Parallel convolution calculation time:  %f ms\n", gpuTime);
    printf("accelerate %f time\n", cpuTime / gpuTime);


    cudaEventDestory(start);
    cudaEventDestory(stop);

    //10.将输出数组从device拷贝到host
    cudaMemcpy(hostP, deviceP, sizeof(float) * width, cudaMemcpyDeviceToHost);


    //11.释放Device上的内存
    cudaFree(deviceN);
    cudaFree(deviceM);
    cudaFree(deviceP);

    for(int i = 0; i < width; i++)
    {
        if(abs(hostCPUTest[i] - hostP[i]) > 1e-5)
        {
            exit(1)
        }
    }

    //12.计算结果写入文件
    writeOutputFile(hostP, width);

    //13.释放Host上内存
    free(hostN);
    free(hostM);
    free(hostP);
    free(hostCPUTest);

    return;

}