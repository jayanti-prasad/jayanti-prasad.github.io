/*-----------------------------------------------------------------
    
 * This program demonstrates the  
   use of OpenMP barrier construct.
   
 * Note that you must supply the number of threads at run time. 
 
 Jayanti Prasad, Nov 12, 2011
 Comments & Suggestions : prasad.jayanti@gmail.com                 
 
 For detail Visit :
 http://www.iucaa.ernet.in/~jayanti/
 ------------------------------------------------------------------- */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<sys/time.h>

int main(int argc, char *argv[]){
  int numthreads,myid;

  if (argc < 2){
    fprintf(stderr,"./a.out <numthreads>\n");
    return(-1);
  }
  
  numthreads = atoi(argv[1]);
  omp_set_num_threads(numthreads);

#pragma omp parallel private(myid)
  {
    myid = omp_get_thread_num();
    if (myid < omp_get_num_threads()/2 )
      system("sleep 3");
    printf("thread %d: before\n",myid);
    
#pragma omp barrier
    printf("thread  %d: after\n",myid);
    
  } 
  return(0);
}
