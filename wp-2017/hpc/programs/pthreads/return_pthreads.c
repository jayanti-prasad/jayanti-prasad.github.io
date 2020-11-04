/*-----------------------------------------------
  PTHREAD : RETURN 
 
  * This programs shows how data can be returned by a subprogram 
    which every threads exectute in parallel.  
 
  [Comments & Suggestion : Jayanti Prasad 
  prasad.jayanti@gmail.com 
  http://www.iucaa.ernet.in/~jayanti/]

  Sun Jan 29 10:10:37 IST 2012
 
  --------------------------------------------------*/
#include <pthread.h>
#include <stdio.h>
#include<stdlib.h>

void* child_thread( void * param ){
 long id, jd; 
 id = (long )param;
 jd = id *id; 
 return (void *)jd;
}

int main(int argc, char *argv[]){
  long  i;
  pthread_t *thread;
  long  *return_value;
  int num_threads;  

  if(argc < 2){
    fprintf(stderr,"./return_pthreads  <# threads>\n");
    return(-1);
  }
 
  num_threads = atoi(argv[1]); 
  
  thread = (pthread_t *)malloc(num_threads*sizeof(pthread_t)); 
  return_value=(long *)malloc(num_threads*sizeof(long )); 

  for (i=0; i<num_threads; i++ ){
    pthread_create(&thread[i],NULL,&child_thread,(void*)i );
  }
  
  for (i=0; i<num_threads ; i++ )  {
    pthread_join(thread[i], (void**)&return_value[i] );
    printf( "input = %ld output=%ld  \n",i, return_value[i] );
  }
  
  return(0);
  
}
