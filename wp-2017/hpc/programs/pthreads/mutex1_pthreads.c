/*-----------------------------------------------
  PTHREADS : MUTEX 
  
  * This program demonstrates how a global variable can 
  be locked using 'mutex' locks.

    
  [Comments & Suggestion : Jayanti Prasad 
  prasad.jayanti@gmail.com 
  http://www.iucaa.ernet.in/~jayanti/]

  Sun Jan 29 10:10:37 IST 2012
  
  --------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *functionC();
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int  counter = 0;

int main(int argc, char *argv[]){
  int rc, num_threads;
  pthread_t *thread;
  long l;  
 
 if(argc < 2){
    fprintf(stderr,"./mutex_pthreads  <# threads>\n");
    return(-1);
  }
 
  num_threads = atoi(argv[1]);
  
  for(l=0; l < num_threads; l++){
    if((rc=pthread_create(&thread[l],NULL,&functionC,NULL))){
      printf("Error With %d\n",rc);
      return(-1);
    }
  }
  
  for(l=0; l < num_threads; l++){
    pthread_join(thread[l],NULL);
  }
  return(0);
  
}

void *functionC(){
  //pthread_mutex_lock(&mutex1 );
  counter++;
  printf("Counter value: %d\n",counter);
  //pthread_mutex_unlock( &mutex1 );
}

