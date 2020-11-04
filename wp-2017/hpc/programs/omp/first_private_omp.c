/*-----------------------------------------------------------------
 * This program  demonstrates the use OpenMP Schedule.
 
 * Note that you must supply the number of threads at runtime. 
 
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
  int numthreads,i,indx;
  int myid;

  if (argc < 2){
    fprintf(stderr,"./a.out <numthreads>\n");
    return(-1);
  }

  numthreads = atoi(argv[1]);
  omp_set_num_threads(numthreads);
  indx  = 3;

#pragma omp parallel firstprivate(indx) private(myid)  
//#pragma omp parallel private(myid,indx)   // this is wrong !
  {
    myid  = omp_get_thread_num();
    indx += myid;
    printf("my id=%d indx=%d\n",myid,indx);
  } 
  printf("After the parallel region: indx=%d\n",indx);
  return(0);

}
