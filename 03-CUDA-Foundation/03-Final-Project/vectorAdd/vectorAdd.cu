
/////////////////////////////////////////////////////////////////////////////////////// 理论讲解部分
/* __global__ void add(int *a, int *b, int *c)
{
    *c = *a + *b;
}


int main()
{
    int a = 1, b = 2, c;
    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, sizeof(int));
    cudaMalloc((void **)&d_b, sizeof(int));
    cudaMalloc((void **)&d_c, sizeof(int)); 
    ...

    cudaMemcpy(d_a, &a, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, &b, sizeof(int), cudaMemcpyHostToDevice);
    add<<<1, 1>>>(d_a, d_b, d_c);
    cudaMemcpy(&c, d_c, sizeof(int), cudaMemcpyDeviceToHost);
    ...

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    return 0;
} */


/////////////////////////////////////////////////////////////////////////////////////// 实战项目部分（线程计算是乱序的）

/* 
CUDA编程实现：对比不同线程块规模下，二维矩阵并行加法性能
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

void initialData(float *in, int size)
{
    time_t t;
    srand((unsigned)time(&t));
    for(int i = 0; i < size; i++)
    {
        in[i] = (float)(rand() & 0xffff) / 1000.0f;
    }
}

double cpuSecond()
{
    LARGE_INTEGER frequency, start;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    return (double)start.QuadPart / (double)frequency.QuadPart;
}

void sumMatrix2D_CPU(float *a, float *b, float *c, int nx, int ny)
{
    for(int j = 0; j < ny; j++)
    {
        for(int i = 0; i < nx; i++)
        {
            int idx = i + j * nx;
            c[idx] = a[idx] + b[idx];
        }
    }
}

__global__ void sumMatrix_kernel(float *a, float *b, float *c, int nx, int ny)
{
    int ix = threadIdx.x + blockDim.x * blockIdx.x;
    int iy = threadIdx.y + blockDim.y * blockIdx.y;
    int idx = ix + iy * nx;
    if(ix < nx && iy < ny)
    {
        c[idx] = a[idx] + b[idx];
    }
}




int main(int argc, char **argv)
{
    int nx = 1<<14, ny = 1<<14;
    int width = nx * ny;

    float *hostA = (float *)malloc(sizeof(float) * width);
    float *hostB = (float *)malloc(sizeof(float) * width);
    float *hostC = (float *)malloc(sizeof(float) * width);
    float *hostCPUTest = (float *)malloc(sizeof(float) * width);

    initialData(hostA, width);
    initialData(hostB, width);

    double cpuStart = cpuSecond();
    sumMatrix2D_CPU(hostA, hostB, hostCPUTest, nx, ny);
    double cpuTime = (cpuSecond() - cpuStart) * 1000;
    printf("CPU time: %f ms\n", cpuTime);

    float *deviceA, *deviceB, *deviceC;
    cudaMalloc((void **)&deviceA, sizeof(float) * width);
    cudaMalloc((void **)&deviceB, sizeof(float) * width);
    cudaMalloc((void **)&deviceC, sizeof(float) * width);

    cudaMemcpy(deviceA, hostA, sizeof(float) * width, cudaMemcpyHostToDevice);
    cudaMemcpy(deviceB, hostB, sizeof(float) * width, cudaMemcpyHostToDevice);

    int dimx = 32, dimy = 32;
    if(argc > 2)
    {
        dimx = atoi(argv[1]);
        dimy = atoi(argv[2]);
    }
    dim3 dimBlock(dimx, dimy);
    dim3 dimGrid((nx - 1)/dimx + 1, (ny - 1)/dimy + 1);

    cudaEvent_t start, stop;
    float gpuTime = 0.0f;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start);

    sumMatrix_kernel<<<dimGrid, dimBlock>>>(deviceA, deviceB, deviceC, nx, ny);

    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&gpuTime, start, stop);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    cudaDeviceSynchronize();

    printf("GPU time: %f ms\n", gpuTime);
    printf("Speed up: %f\n", cpuTime / gpuTime);

    cudaMemcpy(hostC, deviceC, sizeof(float) * width, cudaMemcpyDeviceToHost);

    for(int i = 0; i < width; i++)
    {
        if(fabs(hostCPUTest[i] - hostC[i]) > 1e-5)
        {
            printf("Result mismatch!\n");
            exit(1);
        }
    }

    cudaFree(deviceA);
    cudaFree(deviceB);
    cudaFree(deviceC);

    free(hostA);
    free(hostB);
    free(hostC);
    free(hostCPUTest);

    printf("Success!\n");
    return 0;
}