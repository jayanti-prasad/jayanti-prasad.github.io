/*-----------------------------------------------
  PTHREADS : SUMMATION  2 
  
  * This program demonstrate the use of pthreads for adding 
  the elements of an array in parallel.
  
  * Note that the subprogram returns a value which is collected
  at the time of joining the threads.
  
  * The array which has to be added is passed as global data.
  
  * This is a general program since in this the main program 
  exchanges a structure with the subprogram which makes possible
  to share any type of data.

  
  [Comments & Suggestion : Jayanti Prasad, 
  prasad.jayanti@gmail.com, 
  http://www.iucaa.ernet.in/~jayanti/]
  
  Sun Jan 29 10:10:37 IST 2012
  
 --------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

float *x; 

typedef struct{
  int thread_id;
  int chunk;
  float data; 
} thread_data;


/* This is the function which will be executed by every thread */

void *tfunc(void *arg){
  thread_data *p = (thread_data *)arg;
  long  id = p->thread_id;
  int i, np  = p->chunk;
  float y;
    
  y = 0.0;
  for(i=id*np; i <(id+1)*np; i++)
    y+=x[i];
  
  //   i=10;
  //  while (i==i){
  //}
  
  p->data = y; 
  // this is how the pointer to a structure is feed.  
  
  return (void *)p;
  
}

int main(int argc, char *argv[]){
  int np,num_threads,num_points;
  pthread_t *t;
  thread_data *q;  
  long i;
  float sum; 
  
  if(argc < 3){
    fprintf(stderr,"./summation2_pthreads  <# points>  <# threads>\n");
    return(-1);
  }
  
  
  
  num_points  = atoi(argv[1]);
  num_threads = atoi(argv[2]);
  
  np = (int) (num_points/num_threads);
  
  x = (float *)malloc(num_points*sizeof(float)); 
  t = (pthread_t *)malloc(num_threads*sizeof(pthread_t)); 
  q = (thread_data *)malloc(num_threads*sizeof(thread_data)); 
  
  for(i=0; i < num_points; i++)
    x[i]=(float) i; 
  
  for(i=0; i < num_threads; i++){
    q[i].thread_id = i;
    q[i].chunk = np; 
    pthread_create(&t[i],NULL,tfunc,(void *)(q+i));
  }
  
  sum = 0.0;
  for(i=0; i < num_threads; i++){
    pthread_join(t[i], (void**)&q[i] );
    sum+=q[i].data;
  }
  
  printf("sum=%.6f\n",sum); 
  
  return(0);
}
