/*------------------------------------------------------------------

  PTHREADS: COMPUTE_PI 

 * This program demonstartes how the value of Pi can be computed by
   numerically integrating 1/(1+x*x) between limits 0 and 1 using 
   pthreads.

 * The main program send the id of the thread to the function 'func'
   one the basis of which the function sets the limit over which 
   the thread has to do numerical integration.  

 * The function replaces the value of id with the partial sum.

 * Finally all the partial sums are added when threads are joined. 

                                --Jayanti Prasad, October 29, 2011
                  Suggestions & Comments :prasad.jayanti@gmail.com  
                   for detail : http://www.iucaa.ernet.in/~jayanti/     

-------------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>

double   PI25DT = 3.141592653589793238462643;

int num_points, num_threads; 
double h; 

/* This is the function which does integration */

void *func (void *arg){
 double *x,y, t;
 x = (double *)arg;
 int tid = (int )*x;  
 int i;

 y = 0.0;
 for(i=tid*num_points/num_threads; i < (tid+1)*num_points/num_threads; i++){
    t = (double )i * h;
    y+=4.0/(1.0+t*t);  
 }
 *x=y; 
}

/* This is the main program */

int main(int argc, char *argv[]){
 int i,ir;
 pthread_t *thread_id;
 double *data,sum; 

 if(argc < 2){
    fprintf(stderr,"./compute_pi_pthreads <num_points> <num_threads>\n");
    return(-1);
  } 

  num_points = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  h = 1.0/num_points;
 
  thread_id = (pthread_t *)malloc(num_threads*sizeof(pthread_t));
  data  = (double  *)malloc(num_threads*sizeof(double));

 /* create threads and send the data */

  for(i=0; i < num_threads; i++){
       data[i] = (double) i; 
      ir = pthread_create(&thread_id[i],NULL,func, (void *)&data[i]); 
  }
 
/* join the threads */

  sum = 0.0;
  for(i=0; i < num_threads; i++){
    pthread_join(thread_id[i],NULL);
    sum+= h*data[i]; 
  }

  printf("sum=%.12g, error=%.12g\n",sum,(sum-PI25DT));

return(0);
}



