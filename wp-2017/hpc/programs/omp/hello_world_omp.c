/*-----------------------------------------------------------------
    
 * This is the Hello World Program which demonstrates the 
 use of multiple threads.
 
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
  int myid, numthreads;
  
  if (argc < 2){
    fprintf(stderr,"./hello_wolrd_omp <num of threads>\n");
    return(-1);
  }

  numthreads = atoi(argv[1]);

  omp_set_num_threads(numthreads);
  
#pragma omp parallel 
  {
    
    myid = omp_get_thread_num();
    
    numthreads = omp_get_num_threads();
    
    printf("Hello World from  %d of %d threads ! \n",myid,numthreads);
    
  }

  return(0);
}

