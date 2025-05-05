#include<iostream>
#include<vector>
using namespace std;

__global__ void vecAdd(int *A, int *B, int *C, int size){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if(tid<size){
        C[tid] = A[tid] + B[tid];
    }
}

int main(){

    int size = 5;
    vector<int> A = {1,2,3,4,5};
    vector<int> B = {2,3,4,5,6};
    vector<int> C;
    C.resize(size);

    int allocSize = size*sizeof(int);
    int *X, *Y, *Z;

    cudaMalloc(&X, allocSize);
    cudaMalloc(&Y, allocSize);
    cudaMalloc(&Z, allocSize);

    cudaMemcpy(X, A.data(), allocSize, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B.data(), allocSize, cudaMemcpyHostToDevice);

    vecAdd<<<1, 255>>>(X, Y, Z, size);

    cudaMemcpy(C.data(), Z, allocSize, cudaMemcpyDeviceToHost);

    for(int i=0; i<size; i++){
        cout<<C[i]<<" ";
    }

    return 0;
}