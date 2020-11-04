/*-----------------------------------------------
  PTHREAD : HELLO WORLD 1
  
  
  * The main program asked threads to print 'Hello World'
  with their thread id.
  
  * Note that here nothing is returned from the subprogram 
  which every thread executes.
  
  [Comments & Suggestion : Jayanti Prasad 
  prasad.jayanti@gmail.com 
  http://www.iucaa.ernet.in/~jayanti/]

  Sun Jan 29 10:10:37 IST 2012
  
  --------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *tfunc(void *arg){
  long    my_id = (long) arg;
  fprintf(stdout," Hello World from  %ld\n",my_id);
}

int main(int argc, char *argv[]){
  int num_threads;
  long i;
  pthread_t *t;
  
  if(argc < 2){
    fprintf(stderr,"./hello_world <# threads>\n");
    return(-1);
  }
  
  num_threads=atoi(argv[1]);
  
  t = (pthread_t *)malloc(num_threads*sizeof(pthread_t)); 
  
  for(i=0; i < num_threads; i++){
    pthread_create(&t[i],NULL,tfunc,(void *)i);
  }
  
  for(i=0; i < num_threads; i++){
    pthread_join(t[i],NULL) ;
  }
  
  return(0);
}
