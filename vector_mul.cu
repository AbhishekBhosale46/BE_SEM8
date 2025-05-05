#include <iostream>
#include <vector>
using namespace std;

#define N 3  // Matrix size N x N

// CUDA kernel for matrix multiplication
__global__ void matMul(int* A, int* B, int* C, int n) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;  // Row index
    int col = blockIdx.x * blockDim.x + threadIdx.x;  // Column index

    if (row < n && col < n) {
        int sum = 0;
        for (int k = 0; k < n; ++k)
            sum += A[row * n + k] * B[k * n + col];

        C[row * n + col] = sum;
    }
}

int main() {
    int size = N * N;
    int bytes = size * sizeof(int);

    // Host matrices
    vector<int> h_A = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };
    vector<int> h_B = {
        9, 8, 7,
        6, 5, 4,
        3, 2, 1
    };
    vector<int> h_C(size);  // Result matrix

    // Device matrices
    int *d_A, *d_B, *d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    // Copy data to device
    cudaMemcpy(d_A, h_A.data(), bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B.data(), bytes, cudaMemcpyHostToDevice);

    // Kernel launch: one thread per element
    dim3 threadsPerBlock(N, N);
    dim3 blocksPerGrid(1, 1);

    matMul<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);

    // Copy result back
    cudaMemcpy(h_C.data(), d_C, bytes, cudaMemcpyDeviceToHost);

    // Print result
    cout << "Result matrix C:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << h_C[i * N + j] << "\t";
        cout << endl;
    }

    // Cleanup
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    return 0;
}
