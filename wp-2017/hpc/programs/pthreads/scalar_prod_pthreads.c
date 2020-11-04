/*--------------------------------------------------------

  PTHREADS : SCALAR PRODUCT 

 * This program computes the scalar product of two vectors 
   using pthreads.

 * At present the vector are passes as global variables, however,
   one can use other better schemes. 
 
 * Note that data to threads is passes using some data structure. 

 * This program also uses a timing function to compute the time 
   taken by the parallel section of the  program.

  * This program also demonstrate the use of mutex locks.

  --Jayanti Prasad, October 29, 2011
  Suggestions & Comments :prasad.jayanti@gmail.com  
  for detail : http://www.iucaa.ernet.in/~jayanti/     
-----------------------------------------------------------*/
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

int time_estimate(struct timeval, struct timeval);

typedef struct{
  int thread_id;
  int num_threads;
  int nsize;
  
} thread_data;

float *vecA, *vecB,global_sum ;
int vec_length; 

pthread_mutex_t mutex_sum = PTHREAD_MUTEX_INITIALIZER;

/* This is the function which every threads computes in parallel */

void * VecSum(void *arg){
  thread_data *p = (thread_data *)arg; 
  int myid = p->thread_id;
  int nthreads=p->num_threads;
  int n = p->nsize;
  int i;
  float local_sum; 
 
  for(i=myid*n/nthreads;  i < (myid+1)*n/nthreads; i++)
    local_sum+=vecA[i] * vecB[i];
  
  fprintf(stdout,"local_sum=%.2f\n",local_sum); 
  
  /*updating global sum using mutex lock */
  
  pthread_mutex_lock(&mutex_sum);
  global_sum += local_sum;
  pthread_mutex_unlock(&mutex_sum);
 
  return;
	
} 

/* This is the main program */

int  main(int argc, char *argv[]){
  /*variable declaration */
  int ret_count;
  pthread_t * threads;
  pthread_attr_t pta;
  int  i, num_threads, vec_length;
  thread_data *arg; 
  struct timeval  t1,t2;
  struct timezone tzp;
  
  if (argc < 2){
    fprintf(stderr,"./scalar_prod_pthreads   <vect size> <num threads>\n");
    return(-1);
  }
  
  vec_length = abs(atoi(argv[1]));
  num_threads  = abs(atoi(argv[2]));
  
  vecA = (float  *) malloc(sizeof(float) * vec_length);
  vecB = (float  *) malloc(sizeof(float) * vec_length);
  arg  = (thread_data *)malloc(num_threads*sizeof(thread_data));
  
  pthread_attr_init(&pta);
  
  threads = (pthread_t *) malloc(sizeof(pthread_t) * num_threads);
  
  for(i=0; i < vec_length; i++){
    vecA[i] = (float ) i+1;
    vecB[i] = 1.0;
  }

  /* Now find out the starting time */
  
  gettimeofday (&t1, &tzp);
  
  /*Thread Creation */
  for (i  = 0; i < num_threads;i++)    {
    arg[i].thread_id = i;
    arg[i].num_threads = num_threads;
    arg[i].nsize = vec_length;
    ret_count=pthread_create(&threads[i],NULL,VecSum, (void *) (arg+i));
  }
  
  /*joining thread */
  for (i = 0; i < num_threads;i++) {
    ret_count=pthread_join(threads[i], NULL);
    
  }
   
  /* Find out the final time */

  gettimeofday (&t2, &tzp);
 
   
  printf("A   = ");
  for(i=0; i < vec_length; i++)
    fprintf(stdout," %.2f ",vecA[i]); 
  printf("\n");
  
  printf("B   = ");
  for(i=0; i < vec_length; i++)
    printf(" %.2f ",vecB[i]); 
  printf("\n");
  

  printf("A.B =  %.6f\n ",global_sum);
  
  ret_count=pthread_attr_destroy(&pta);
  
  time_estimate(t1,t2);
  
  return (0);
  
} 

/* This function computes the time difference */

int time_estimate(struct timeval t1, struct timeval t2){
  float t;
  
  t = (t2.tv_sec-t1.tv_sec) + (t2.tv_usec-t1.tv_usec)/1000000.0;
  
  printf("Time [seconds]= %12.6f \n",t);
  
  return(0);
}
