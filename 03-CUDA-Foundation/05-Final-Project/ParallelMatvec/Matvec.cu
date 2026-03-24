/* 
单精度矩阵向量乘
 */

#include <stdio.h>
#include <math.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>

//朴素实现
__global__ void sgemvNative(float *A, float *X, float *Y, int M, int N)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if(i < M)
    {
        float tmp = 0;
        for(int j = 0; j < N; j++)
            tmp += A[i * N + j] * X[j];
        Y[i] = tmp;
    }
}

//使用合并访存优化
__global__ void sgemvCoalesced(float *At, float *X, float *Y, int M, int N)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if(i < M)
    {
        float tmp = 0;
        for(int j = 0; j < N; j++)
            tmp += At[j * M + i] * X[j];
        Y[i] = tmp;
    }
}

//使用常量内存优化
__constant__ float d_CX[(1 << 14)];
__global__ void sgemvConstant(float *At, float *X, float *Y, int M, int N)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if(i < M)
    {
        float tmp = 0;
        for(int j = 0; j < N; j++)
            tmp += At[j * M + i] * d_CX[j];
        Y[i] = tmp;
    }
}

//使用共享内存优化
//block_size 分块大小
template <size_t block_size>
__global__ void sgemvSharedMemory(float *At, float *X, float *Y, int M, int N)
{
    __shared__ float s_X[block_size];
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if(i < M)
    {
        float tmp = 0;
        int j_last_block_index = N / block_size * block_size;
        #pragma unroll
        for(int j = 0; j < j_last_block_index; j += block_size)
        {
            s_X[threadIdx.x] = X[j + threadIdx.x];
            __syncthreads();
            for(int k = 0; k < block_size; k++)
            {
                tmp += At[(k+j) * M + i] * s_X[k]; //A[i][j] At[j+k][i] * s_X[k]
            }
            __syncthreads();
        }
        if(j_last_block_index != N)
        {
            s_X[threadIdx.x] = X[j_last_block_index + threadIdx.x];
            __synthreads();
            #pragma unroll
            for(int k = 0; k < (N - j_last_block_index); k++)
            {
                tmp += At[(k+j_last_block_index) * M + i] * s_X[k];
            }
        }
        Y[i] = tmp;
    }
}


bool verifyResult(float *h_Y_base, float *h_Y, int M)
{
    double eps = 1.e-6;
    bool correct = true;
    for(int i = 0; i < M; i++)
    {
        double abs_err = fabs(h_Y[i] - h_Y_base[i]);
        double dot_length = M;
        double abs_val = fabs(h_Y[i]);
        double rel_err = abs_err / abs_val / dot_length;
        if(rel_err > eps)
        {
            printf("Error! Y[%d]=%.8f, ref=%.8f error term is> %E\n", i, h_Y[i], h_Y_base[i], eps);
            correct = false;
            break;
        }
    }
    return correct;

}




int main(int argc, char **argv)
{
    size_t M = 1 << 14, N = 1 <<14;
    if(argc == 3)
    {
        M = 1 << (atoi(argv[1]));
        N = 1 << (atoi(argv[2]));
    }

    float *h_A = (float *)malloc(M * N * sizeof(float));
    float *h_At = (float *)malloc(N * M * sizeof(float));
    float *h_X = (float *)malloc(N * sizeof(float));
    float *h_Y = (float *)malloc(M * sizeof(float));
    float *h_Y_base = (float *)malloc(M * sizeof(float));

    float *d_A;
    float *d_At;
    float *d_X;
    float *d_Y;
    cudaMalloc(&d_A, M * N * sizeof(float));
    cudaMalloc(&d_At, N * M * sizeof(float));
    cudaMalloc(&d_X, N * sizeof(float));
    cudaMalloc(&d_Y, M * sizeof(float));

    double msPerMatrixVectorMul[5] = {0,0,0,0,0};
    double gflops[5] = {0,0,0,0,0};
    double flopsPerMatrixVectorMul = 2.0 * M * N;

    // A X数组初始化
    for(int j = 0; j < N; j++)
    {
        h_X[j] = (float)j/N;
        for(int i = 0; i < M; i++)
        {
            h_At[j * M + i] = h_A[i * N + j] = 1.0;
        }
    }
    printf("Matrix A: %d*%d, Vector X: %d, Vector Y: %d\n", M, N, N, M);

    cudaMemcpy(d_A, h_A, sizeof(float) * M * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_At, h_At, sizeof(float) * N * M, cudaMemcpyHostToDevice);
    cudaMemcpy(d_X, h_X, sizeof(float) * N, cudaMemcpyHostToDevice);


    float msTotal = 0;
    int nIter = 10;

    const int block_size = 1 << 7;
    int grid_size = (M + block_size -1) / block_size;


    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    
    // ===================== CUBLAS =====================
    cublasHandle_t blas_handle;
    cublasCreate(&blas_handle);
    float alpha = 1.0, beta = 0;
    cudaMemcpy(d_Y, h_Y_base, M * sizeof(float), cudaMemcpyHostToDevice);
    cudaEventRecord(start);
    for(int i = 0; i < nIter; i++)
    {
        cublasSgemv(blas_handle, CUBLAS_OP_T,
                    N, M, &alpha, d_A,
                    N, d_X, 1, &beta, d_Y, 1);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&msTotal, start, stop);
    cublasDestroy(blas_handle);
    cudaMemcpy(h_Y_base, d_Y, M * sizeof(float), cudaMemcpyDeviceToHost);
    msPerMatrixVectorMul[0] = msTotal/nIter;
    gflops[0] = (flopsPerMatrixVectorMul * 1.0e-9f) / (msPerMatrixVectorMul[0] / 1000.0f);
    printf("cublas 性能=%.2f GFlop/s,运行时间= %.3f ms\n\n", gflops[0], msPerMatrixVectorMul[0]);



    // ===================== Native =====================
    cudaMemcpy(d_Y, h_Y, M * sizeof(float), cudaMemHostToDevice);
    cudaEventRecord(start);
    for(int i = 0; i < nIter; i++)
    {
        sgemvNative<<<grid_size, block_size>>>(d_A, d_X, d_Y, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&msTotal, start, stop);
    cudaMemcpy(h_Y, d_Y, M * sizeof(float), cudaMemcpyDeviceToHost);
    msPerMatrixVectorMul[1] = msTotal/nIter;
    gflops[1] = (flopsPerMatrixVectorMul * 1.0e-9f) / (msPerMatrixVectorMul[1] / 1000.0f);
    printf("sgemvNative 性能=%.2f GFlop/s,运行时间= %.3f ms\n\n", gflops[1], msPerMatrixVectorMul[1]);
    printf("%s\n", verifyResult(h_Y_base, h_Y, M) ? "Accuracy check passed" : "Accuracy check failed");
    printf("achieve cublas %f%\n\n", gflops[1] / gflops[0] * 100.0);


    // ===================== Coalesced =====================
    memset(h_Y, 0.0, M * sizeof(float));
    cudaMemcpy(d_Y, h_Y, M * sizeof(float), cudaMemHostToDevice);
    cudaEventRecord(start);
    for(int i = 0; i < nIter; i++)
    {
        sgemvCoalesced<<<grid_size, block_size>>>(d_At, d_X, d_Y, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&msTotal, start, stop);
    cudaMemcpy(h_Y, d_Y, M * sizeof(float), cudaMemcpyDeviceToHost);
    msPerMatrixVectorMul[2] = msTotal/nIter;
    gflops[2] = (flopsPerMatrixVectorMul * 1.0e-9f) / (msPerMatrixVectorMul[2] / 1000.0f);
    printf("sgemvCoalesced  性能=%.2f GFlop/s,运行时间= %.3f ms\n\n", gflops[2], msPerMatrixVectorMul[2]);
    printf("%s\n", verifyResult(h_Y_base, h_Y, M) ? "Accuracy check passed" : "Accuracy check failed");
    printf("achieve cublas %f%\n\n", gflops[2] / gflops[0] * 100.0);


    // ===================== Constant =====================
    if(N <= (1 << 14))
    {
        cudaMemcpyToSymbol(d_CX, h_X, sizeof(float) * N);
        memset(h_Y, 0.0, M * sizeof(float));
        cudaMemcpy(d_Y, h_Y, M * sizeof(float), cudaMemHostToDevice);
        cudaEventRecord(start);
        for(int i = 0; i < nIter; i++)
        {
            sgemvConstant<<<grid_size, block_size>>>(d_At, d_X, d_Y, M, N);
        }
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        cudaEventElapsedTime(&msTotal, start, stop);
        cudaMemcpy(h_Y, d_Y, M * sizeof(float), cudaMemcpyDeviceToHost);
        msPerMatrixVectorMul[3] = msTotal/nIter;
        gflops[3] = (flopsPerMatrixVectorMul * 1.0e-9f) / (msPerMatrixVectorMul[3] / 1000.0f);
        printf("sgemvConstant  性能=%.2f GFlop/s,运行时间= %.3f ms\n\n", gflops[3], msPerMatrixVectorMul[3]);
        printf("%s\n", verifyResult(h_Y_base, h_Y, M) ? "Accuracy check passed" : "Accuracy check failed");
        printf("achieve cublas %f%\n\n", gflops[3] / gflops[0] * 100.0);
    }


    // ===================== Shared Memory =====================
    memset(h_Y, 0.0, M * sizeof(float));
    cudaMemcpy(d_Y, h_Y, M * sizeof(float), cudaMemHostToDevice);
    cudaEventRecord(start);
    for(int i = 0; i < nIter; i++)
    {
        sgemvSharedMemory<block_size><<<grid_size, block_size>>>(d_At, d_X, d_Y, M, N);
    }
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);
    cudaEventElapsedTime(&msTotal, start, stop);
    cudaMemcpy(h_Y, d_Y, M * sizeof(float), cudaMemcpyDeviceToHost);
    msPerMatrixVectorMul[4] = msTotal/nIter;
    gflops[4] = (flopsPerMatrixVectorMul * 1.0e-9f) / (msPerMatrixVectorMul[4] / 1000.0f);
    printf("sgemvSharedMemory 性能=%.2f GFlop/s,运行时间= %.3f ms\n\n", gflops[4], msPerMatrixVectorMul[4]);
    printf("%s\n", verifyResult(h_Y_base, h_Y, M) ? "Accuracy check passed" : "Accuracy check failed");
    printf("achieve cublas %f%\n\n", gflops[4] / gflops[0] * 100.0);


    cudaEventDestory(start);
    cudaEventDestory(stop);


    cudaFree(d_A);
    cudaFree(d_At);
    cudaFree(d_X);
    cudaFree(d_CX);
    cudaFree(d_Y);

    free(h_A);
    free(h_At);
    free(h_X);
    free(h_Y);
    free(h_Y_base);

    printf("Success!\n");
    return 0;

}