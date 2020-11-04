/*-----------------------------------------------------------------
 * This program  demonstrates the use OpenMP last private.
 
 * Note that you must supply the number of threads and the number of points at runtime. 
 
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
  int numthreads,i,n,indx,myid;

  if (argc < 3){
    fprintf(stderr,"./a.out <numthreads> <num points> \n");
    return(-1);
  }

  numthreads = atoi(argv[1]);
  omp_set_num_threads(numthreads);
  n = atoi(argv[2]); 

 #pragma omp parallel for private (i) lastprivate(indx) 
//#pragma omp parallel for private (i) private(indx) // this is wrong !

for(i=0; i < n; i++){
   indx  = i; 
}

printf("After the parallel region: indx=%d\n",indx);
 
 return(0);
}
