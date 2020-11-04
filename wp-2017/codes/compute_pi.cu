/*-------------------------------------------------------------------------
!    THIS SOFTWARE IS PROVIDED "AS IS", AND JAYANTI PRASAD  MAKE NO
     REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPlIED.
     By way of example, but not limitation,
     JAYANTI PRASAD MAKE NO REPRESENTATIONS OR WARRANTIES OF
     MERCHANTABIlITY OR FITNESS FOR ANY PARTICUlAR PURPOSE OR THAT
     THE USE OF THE lICENSED SOFTWARE OR DOCUMENTATION WIll NOT INFRINGE
     ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS.
-------------------------------------------------------------------*/

/*--------------------------- Parallel Programming with CUDA : Demo 1 ------------->>>

 This program computes the value of pi by integrating 1/(1+x^2) between limits [0,1]
 and demonsrate the use of cuda.

 In the present example cuda threads are in the form of a three dimensional block  
 of size 4 X 4 X 4 and which a member of 1 grid of size 1 X 1 X 1.

 Total number of cuda threads (nthreads) = number of grids X number of threads in a block. 

 User has to specify the number of point (npoints) used for the integartion at run time. 

 This program contains two parts : one compute (which runs on the device i.e., GPU, 
 and another which runs on the host i.e., the CPU.

 The number of compuations done by a thread = npoints/nthreads

 Each thread computes a local sum and finally all local sums are added in the local sum of
 the thread with id 0 


Important CUDA concepts used in the program:

 1. cudaMalloc : used to assign memory on the device i.e., GPU 
 2. cudaMemcpy : used to copy the value of a variable from the GPU memory space to CPU 
 3. dim3 : this is type of grid and blocks and can be used to specify the dimensionality 
 4. cuda calling fasion:

    compute <<<dimGrid, dimBlock>>>(local_sum,nval,BLOCK_SIZE);

  by using <<< >>> we can tell the GPU that how many grid or blocks should be used 
  to arrange cuda threads.


CUDA Philosophy:
  People who are familer with shared memory programming (pthread,opneMP) can recall that 
  there is just one memory space which can shared by all the threads. In case of CUDA 
  there are two memory spaces, one for CPU and another for GPU. Programmer has to copy the 
  values of variables from one space to another using cudaMemcpy function.
 

 I think this should be good enough for you to get strated with cuda ! 

 You can talk to me if you are futher interested in learning cuda like me. 

                              Jayanti Prasad (prasad.jaaynti@gmail.com)
                              Jan 21, 2010  
<<<-------------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<cuda.h>

#define BLOCK_SIZE 4 

__global__ void compute(float *local_sum, float nval, int threadDim){
  
  int i,tidx,tidy,tidz,myid,nthreads;   
  float x,sum,h,tmp;
  
  tidx = threadIdx.x;
  tidy = threadIdx.y;
  tidz = threadIdx.z;
  
  myid = tidz + threadDim*(tidy+threadDim*tidx);
  nthreads = threadDim * threadDim * threadDim;
  
  h = 1.0/nval; 
  sum = 0.0;
  x = 0.0;
  
  local_sum[myid] = 0.0;
  
  for(i= myid + 1; i  <= nval; i+= nthreads)
    {
      x = h * ( (float)i - 0.5 );
      sum += (4.0 /(1.0 + x*x));
    }
  
  local_sum[myid] = h * sum;
  
  __syncthreads();
  
  if( myid == 0 )
    {
      tmp = 0.0f;
      for(i = 0; i  < nthreads;i++)
	tmp  += local_sum[i];
      local_sum[0] = tmp;
    }
}
// this was the device part 

int main (int argc, char *argv[])
{
  float *local_sum; // for devive return variable 
  float *global_sum; // this is for the host (CPU)
  int   nval; // this is for device 
  int   numThread = BLOCK_SIZE*BLOCK_SIZE;
  
  nval = atoi(argv[1]); 
  
  global_sum  = (float*) malloc( sizeof(float));

  cudaMalloc( (void**)&local_sum, numThread * sizeof(float));
  
  dim3 dimGrid(1,1,1);  
  
  dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE,BLOCK_SIZE);
  
  compute <<<dimGrid, dimBlock>>>(local_sum,nval,BLOCK_SIZE);
  
  cudaMemcpy((void*)global_sum, (void*)local_sum, sizeof(float),cudaMemcpyDeviceToHost );
  
  printf( "PI = %2.14f for %d # points\n", *global_sum,nval);
  
  cudaFree(local_sum);
  
  free(global_sum);
  
  return(0); 
  
}
