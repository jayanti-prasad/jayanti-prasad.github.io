/*-----------------------------------------------------------------
  
 * This program demonstrates the use of OpenMP critical  construct.
 
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


int main(int argc, char *argv[]){
  int i, num_threads,n,TID, sumLocal,sum,*a;
  
  if (argc < 2){
    fprintf(stderr,"./timer_omp <num threads> <num_points> \n");
    return(-1);
   }
  
  num_threads = atoi(argv[1]);
  n = atoi(argv[2]);
  a = (int *)malloc(n*sizeof(int));
  
  for(i=0; i < n; i++)
    a[i] = i; 
  
  omp_set_num_threads(num_threads);
  
  sum = 0;
  
#pragma omp parallel shared(n,a,sum) private(TID,sumLocal)
  {
    TID = omp_get_thread_num();
    sumLocal = 0;
#pragma omp for
    for (i=0; i<n; i++)
      sumLocal += a[i];
#pragma omp critical (update_sum)
    {
      sum += sumLocal;
      printf("TID=%d: sumLocal=%d sum = %d\n",TID,sumLocal,sum);
    }
  } 
  
  /*-- End of parallel region --*/
  
  printf("Value of sum after parallel region: %d\n",sum);
  
  return(0);
}
