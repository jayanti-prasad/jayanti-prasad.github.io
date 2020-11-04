/*-----------------------------------------------------------------

 * This is a program which demonstrates how to do scalar product of 
 two n-dimensional vectors  using OpenMP.
   
 * Note that you must supply the number of threads and the number
 of points used for integration at run time. 
 
 Jayanti Prasad, Nov 12, 2011
 Comments & Suggestions : prasad.jayanti@gmail.com                 
 
 For detail Visit :
 http://www.iucaa.ernet.in/~jayanti/
 ------------------------------------------------------------------- */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>


int main(int argc, char *argv[]){
  int nthreads, npoints;
  int i, *A, *B, sum=0.0; 
  
  if (argc < 2){
    fprintf(stderr,"./a.out <numthreads> <numpoints>\n");
    return(-1);
  }
  
 nthreads = atoi(argv[1]);
 npoints  = atoi(argv[2]);
 
 A=(int *)malloc(npoints*sizeof(int)); 
 B=(int *)malloc(npoints*sizeof(int)); 
 
 
 for(i=0; i < npoints; i++){
   A[i] = i;
   B[i] = 1;
 }
 
 
#pragma omp parallel for private(i)  reduction(+:sum)  

 for(i=0; i < npoints; i++){
   sum+=A[i]*B[i];     
   
 }
 
 printf("result=%d\n",sum);

 return(0);
}

