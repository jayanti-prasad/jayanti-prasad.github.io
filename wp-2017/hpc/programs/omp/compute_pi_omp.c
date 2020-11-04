/*-----------------------------------------------------------------

 * This is a program which demonstrates how to do numerical 
   integration using OpenMP.

 * This program compute the value of Pi using numerical integration.

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

double   PI25DT = 3.141592653589793238462643;

int main(int argc, char *argv[]){
  int i, nthreads, npoints;
  double h, x, y, sum=0.0;
  
  if (argc < 2){
    fprintf(stderr,"./a.out <numthreads> <numpoints>\n");
    return(-1);
  }
  
  nthreads = atoi(argv[1]);
  npoints  = atoi(argv[2]);
  
  omp_set_num_threads(nthreads); 
  
  h = 1.0/npoints; 
  
#pragma omp parallel for private (i, x) reduction(+:sum) 
  
  for(i=0; i < npoints; i++){
    x  = (double) i *h;
    sum+=4.0/(1.0+x*x);
  }
  
  
  printf("sum=%.12g, error=%.12g\n",h*sum,(h*sum-PI25DT));
  
  return(0);
  
}

