#include <pthread.h>
#include <stdio.h>
#define            LOOPCONSTANT     100000
#define            THREADS          10

pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
int i,j,k,l,uselock=0;

void *threadfunc(void *parm){
  int   loop = 0;
  
  for (loop=0; loop<LOOPCONSTANT; ++loop) {
    if (uselock) 
      pthread_mutex_lock(&mutex);
    ++i; ++j; ++k; ++l;
    if (uselock) 
      pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(int argc, char **argv){
  pthread_t             threadid[THREADS];
  int                   loop=0;
  pthread_attr_t        pta;
  
  if (argc >=2)
    uselock=atoi(argv[1]);
  
  pthread_attr_init(&pta);
  pthread_attr_setdetachstate(&pta, PTHREAD_CREATE_JOINABLE);
  
  for (loop=0; loop<THREADS; ++loop) {
    pthread_create(&threadid[loop], &pta, threadfunc, NULL);
  }

  for (loop=0; loop<THREADS; ++loop) {
    pthread_join(threadid[loop], NULL);
  }  
    
  pthread_attr_destroy(&pta);
  pthread_mutex_destroy(&mutex);
  
  printf("\nUsing %d threads and LOOPCONSTANT = %d\n",
         THREADS, LOOPCONSTANT);
  printf("Values are: (should be %d)\n", THREADS * LOOPCONSTANT);
  printf("  ==>%d, %d, %d, %d\n", i, j, k, l);
  
  return (0);
}

