/*-----------------------------------------------
  PTHREAD : HELLO WORLD 3
    
  * The main program asked threads to print 'Hello World'
  with their thread id.
  
  * Note that here nothing is returned from the subprogram 
  which every thread executes.

  * In this program a structure is passed to subprogram which 
   is executed by every thread. It makes possible to pass more data to
   thread other than just the id.
   
  [Comments & Suggestion : Jayanti Prasad, 
  prasad.jayanti@gmail.com, 
  http://www.iucaa.ernet.in/~jayanti/]

  Sun Jan 29 10:10:37 IST 2012
  
 --------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef struct{
  int thread_id;
  char msg[100]; 
} thread_data;


/* This is the function which will be executed by every thread */

void *tfunc(void *arg){
  thread_data *p = (thread_data *)arg;
  int my_id = p->thread_id;
  fprintf(stdout," %s from  %d\n",p->msg,my_id);
}

int main(int argc, char *argv[]){
   int num_threads, i;
   pthread_t *t;
   thread_data *q;  
   char msg[100]; 

   if(argc < 2){
      fprintf(stderr,"./hello_world <# threads>\n");
      return(-1);
   }

   num_threads=atoi(argv[1]);
 
   t = (pthread_t *)malloc(num_threads*sizeof(pthread_t)); 
   q = (thread_data *)malloc(num_threads*sizeof(thread_data)); 

   for(i=0; i < num_threads; i++){
     q[i].thread_id = i; 
     sprintf(q[i].msg,"Hello World");  
     pthread_create(&t[i],NULL,tfunc,(void *)(q+i));
   }

   for(i=0; i < num_threads; i++){
       pthread_join(t[i],NULL) ;
  }

return(0);
}
