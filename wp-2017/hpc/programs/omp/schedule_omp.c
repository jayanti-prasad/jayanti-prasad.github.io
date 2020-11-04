#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>

int main(int argc, char *argv[]){
  int numthreads,i,n,myid;

  if (argc < 3){
    fprintf(stderr,"./a.out <numthreads> <num points> \n");
    return(-1);
  }

  numthreads = atoi(argv[1]);
  omp_set_num_threads(numthreads);
  n = atoi(argv[2]); 

//#pragma omp parallel for schedule (static) private(i,myid)
#pragma omp parallel for schedule (dynamic) private(i,myid)
  for(i=0; i < n; i++){
 
    myid = omp_get_thread_num();

    printf("I am thread %d and doing %d\n",myid,i); 

  }

 return(0);
}
