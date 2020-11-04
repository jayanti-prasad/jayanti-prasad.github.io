/*-----------------------------------------------
  PTHREADS : SUMMATION  1 
    
  * This program demonstrate the use of pthreads for adding 
  numbers (integers) up to n.

  * Note that the subprogram returns a value which is collected
  at the time of joining the threads.
  
  * The data to be added, the number of threads and the number of 
  points are global variables. 


  * Note that this is not still a general program since it passes only 
  an integer to the subprogram and gets the same back. I general 
  program must be able to handle arbitray data.
  
  [Comments & Suggestion : Jayanti Prasad, 
  prasad.jayanti@gmail.com, 
  http://www.iucaa.ernet.in/~jayanti/]
  
  Sun Jan 29 10:10:37 IST 2012
  
 --------------------------------------------------*/
#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>

long  n, num_threads; 
long *x; 

void* child_thread(void * param ){
  long id,i,p,y; 
  
  id = (long )param;
  p = n/num_threads;
  y = 0;
  for(i=id*p; i <(id+1)*p; i++)
    y+=x[i];  
  return (void *)y;
}


int main(int argc, char *argv[]){
  long  i;
  pthread_t *thread;
  long  sum,y;
 
 if(argc < 3){
    fprintf(stderr,"./summation1_pthreads  <# points>  <# threads>\n");
    return(-1);
  }
 
  n = atoi(argv[1]); 
  num_threads = atoi(argv[2]); 
  
  thread = (pthread_t *)malloc(num_threads*sizeof(pthread_t)); 
  
  x=(long *)malloc(n*sizeof(long )); 
  
  for(i=0; i < n; i++)
    x[i] = (long) i;
  
  for (i=0; i<num_threads; i++ ){
    pthread_create(&thread[i],0,&child_thread,(void*)i );
  }
  
  sum = 0; 
  for (i=0; i<num_threads ; i++ )  {
    pthread_join(thread[i], (void**)&y );
    sum+=y; 
  }
  
  printf("sum=%ld\n",sum);  
  
  return(0);
  
}
