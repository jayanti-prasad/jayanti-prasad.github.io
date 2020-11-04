/*------------------------------------------------------------------
                        CUDA Example 3
This program compute the sum of two vectrors of size N.
The work is distributed amoung cuda threads which are arranged in blocks.
Every block belongs to some grid and every thread belong to some block.
For simplicity I consider one dimensional grid only. However, blocks are
three dimenional. The number of blocks are computed on the basis of the
size of the blocks and the size of the problem.

number of blocks (dimensionality of 1 d grid)=probelem size (N)/
number of threads in a blocks. 

make sure you get an integer when divide your problem size by the number
of threads in a block. If you are not getting an integer, change the BLOCK_SIZE
accordingly.

Note that in any case you should not have more than 512 threads in a block.

This program has been tested on Nvidia Quadro FX 3700 and found to be working fine.
However, timing has not been checked.
                  -- Jayanti Prasad (prasad.jayanti@gmail.com)
                     Wed May  4 11:54:40 IST 2011 
-------------------------------------------------------------------*/
#include<stdio.h>
#include<cuda.h>

#define BLOCK_SIZE 8

__global__ void VecAdd(float *A, float *B, float *C, int N){

  int tid=threadIdx.x + blockDim.x*(threadIdx.y+blockDim.y * threadIdx.z); 
  int bid=blockIdx.x  + gridDim.x * blockIdx.y; 
 
  int nthreads = blockDim.x * blockDim.y * blockDim.z;
  int nblocks  = gridDim.x * gridDim.y; 

  int id      = tid + nthreads * bid;  
  int i;

  for(i=id; i < N; i+=nthreads*nblocks){
    C[i] = A[i] + B[i];
  }
   __syncthreads();
}

int main(int argc, char *argv[]){
  int i, N,grsz,blsz=BLOCK_SIZE;
  float *h_A,*h_B,*d_A,*d_B,*d_C,*h_C;

  if (argc < 2){
   fprintf(stderr,"./a.out  N [=512,1024 etc.]\n");
   return(-1);
  }

  N =  atoi(argv[1]);

  grsz = (int) N/(blsz*blsz*blsz); 

  printf("number grids = %d\n",grsz); 

  size_t size = N * sizeof(float);
  
  h_A = (float *)malloc(size);
  h_B = (float *)malloc(size);
  h_C = (float *)malloc(size);
  
  cudaMalloc(&d_A,size);
  cudaMalloc(&d_B,size);
  cudaMalloc(&d_C,size);
  
  for(i=0; i < N; i++){
    h_A[i] = (float) i;
    h_B[i] = (float) i+1.0;
    h_C[i] = 0.0;
  }

  cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice); 
  cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
  
  dim3 dimGrid(grsz); // 1 blocks
  dim3 dimBlock(blsz,blsz,blsz);  

  VecAdd<<<dimGrid,dimBlock>>>(d_A, d_B, d_C, N);
  
  cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

  for(i=0; i < N; i++){
    fprintf(stdout,"A=%6.2f B=%6.2f A+B = %6.2f\n",h_A[i],h_B[i],h_C[i]);
  }
  cudaFree(d_A); 
  cudaFree(d_B);
  cudaFree(d_C);
  
  return(0);
}
