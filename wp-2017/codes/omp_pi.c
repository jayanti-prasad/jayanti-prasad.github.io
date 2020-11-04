#include<stdio.h> 
#include<math.h>
#include<omp.h>
#include <sys/time.h>
#include<sys/stat.h>

double func(double); 

int main(int argc, char *argv[]){
  int i,n,nthreads;
  double sum1,h,x,err,tsec; 
  double a  = 0.0, b = 1.0;
  struct timeval  t1,t2;
  struct timezone tzp;

  n = atoi(argv[1]);
  nthreads=atoi(argv[2]); 
  omp_set_num_threads(nthreads);
  
  h = (b-a)/(n-1); 
  sum1 = 0.0;
  gettimeofday (&t1, &tzp);

#pragma omp parallel for  private (x)   reduction(+:sum1) 
  
  for(i = 0; i < n; i++){
    x = a + h *i;
    sum1+= h * func(x);
  }

  gettimeofday (&t2, &tzp);

  err  = fabs(sum1-M_PI)/M_PI; 
  tsec = (t2.tv_sec-t1.tv_sec) + (t2.tv_usec-t1.tv_usec)/1000000.0;
  printf("Pi = %2.14f, Error =%2.14f times=%2.2f sec\n",sum1,err,tsec); 
  return(0); 
}

double func(double x){
  float y; 
  y = 4.0/(1.0+x*x); 
  return(y);;
  
}

