

/* 
CUDA编程实现：多流并行计算三角函数，对比单流性能，练习多流的使用、错误管理、事件计时
*/


#include <stdio.h>

//宏定义：检查API调用是否出错
#define CudaSafeCall(err) __cudaSafeCall(err, __FILE__, __LINE__)

inline void __cudaSafeCall(cudaError err, const char *file, const int line)
{
    if (cudaSuccess != err)
    {
        fprintf(stderr, "cudaSafeCall() failed at %s:%i : %s\n",
                file, line, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}


//宏定义：返回上一个错误，主要用于检查kernel函数
#define CudaCheckError() __cudaCheckError(__FILE__, __LINE__)

inline void __cudaCheckError(const char *file, const int line)
{
    cudaError err = cudaGetLastError();
    if(cudaSuccess != err)
    {
        fprintf(stderr, "CudaCheckError() failed at %s:%i : %s\n",
            file, line, cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}


//kernel函数，计算((sinx)^2 + (cosx)^2)
__global__ void kernel(float *a, int offset)
{
    int id = offset + threadIdx.x + blockIdx.x * blockDim.x;
    float x = (float)id;
    float s = sinf(x);
    float c = cosf(x);
    a[id] = a[id] + (s*s + c*c);
}


int main(int argc, char **argv)
{
    // 流的个数
    int nStreams = (argc > 1) ? atoi(argv[1]) : 4;
    // 线程块的大小
    int blockSize = 256;
    // 总的数据个数
    int n = (1 << 28);
    // 总的数据字节数
    int bytes = n * sizeof(float);
    // 每个流分配的数据个数
    int streamSize = n / nStreams;
    // 每个流分配的数据字节数
    int streamBytes = streamSize * sizeof(float);
    
    float *h_a, *d_a;
    //申请计算结果数据的页锁定主机内存和设备内存
    CudaSafeCall(cudaMallocHost((void **)&h_a, bytes));
    CudaSafeCall(cudaMalloc((void **)&d_a, bytes));
    memset(h_a, 0, bytes);

    
    cudaEvent_t start, stop;
    float ms1 = 0.0, ms2 = 0.0;
    CudaSafeCall(cudaEventCreate(&start));
    CudaSafeCall(cudaEventCreate(&stop));


    //单流（默认流）执行
    CudaSafeCall(cudaEventRecord(start));
    CudaSafeCall(cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice));
    kernel<<<n/blockSize, blockSize>>>(d_a, 0);
    CudaSafeCall(cudaDeviceSynchronize());
    CudaCheckError();
    CudaSafeCall(cudaMemcpy(h_a, d_a, bytes, cudaMemcpyDeviceToHost));
    
    CudaSafeCall(cudaEventRecord(stop));
    CudaSafeCall(cudaEventSynchronize(stop));
    CudaSafeCall(cudaEventElapsedTime(&ms1, start, stop));
    printf("Using a single stream, the time for data transfer and computation is: %fms\n", ms1);


    //使用多个流
    memset(h_a, 0, bytes);
    cudaStream_t *streams = (cudaStream_t *)malloc(nStreams * sizeof(cudaStream_t));
    for(int i = 0; i < nStreams; i++)
    {
        CudaSafeCall(cudaStreamCreate(&streams[i]));
    }

    //多流传输和计算重叠 开始计时
    CudaSafeCall(cudaEventRecord(start));
    for (int i = 0; i < nStreams; i++)
    {
        int offset = i * streamSize;
        CudaSafeCall(cudaMemcpyAsync(d_a + offset, h_a + offset, streamBytes, cudaMemcpyHostToDevice, streams[i]));
        kernel<<<streamSize / blockSize, blockSize, 0, streams[i]>>>(d_a, offset);
        CudaSafeCall(cudaMemcpyAsync(h_a + offset, d_a + offset, streamBytes, cudaMemcpyDeviceToHost, streams[i]));
    }
    for(int i = 0; i < nStreams; i++)
    {
        CudaSafeCall(cudaStreamSynchronize(streams[i]));
    }

    CudaSafeCall(cudaEventRecord(stop));
    CudaSafeCall(cudaEventSynchronize(stop));
    CudaSafeCall(cudaEventElapsedTime(&ms2, start, stop));
    printf("Using %d streams,the time for asynchronous data transfer and computation is: %fms, the bypass ratio is: %.2f\n", nStreams, ms2, (ms1/ms2));

    for(int i = 0; i < nStreams; i++)
    {
        CudaSafeCall(cudaStreamDestroy(streams[i]));
    }
    free(streams);

    CudaSafeCall(cudaEventDestroy(start));
    CudaSafeCall(cudaEventDestroy(stop));
    CudaSafeCall(cudaFree(d_a));
    CudaSafeCall(cudaFreeHost(h_a));

    printf("Success!\n");
    return 0;

}