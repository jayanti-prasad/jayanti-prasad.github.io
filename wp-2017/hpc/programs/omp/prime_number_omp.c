/*-----------------------------------------------------------------

 * This is a program which demonstrates how to find the prime number 
 up to some given number by parallel computation  using OpenMP.
 
 
 * Note that you must supply the number of threads and the number
   of points used for integration at run time. 

   Jayanti Prasad, Nov 12, 2011
   Comments & Suggestions : prasad.jayanti@gmail.com                 

   For detail Visit :
   http://www.iucaa.ernet.in/~jayanti/
------------------------------------------------------------------- */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>

int check_prime(int );

int main(int argc, char *argv[]){
  int num_points, num_threads,num_primes;
  float x, y, z;
  int i, prime,t1,t2; 
  
  if (argc < 2){
    fprintf(stderr,"./timer_omp <num threads> <num_points> \n");
    return(-1);
   }
  
  num_threads = atoi(argv[1]);
  num_points = atoi(argv[2]);
  
  omp_set_num_threads(num_threads);
  
  num_primes=0;
  
  t1 = omp_get_wtime ();
  

#pragma omp parallel for private(i,prime)   reduction(+ : num_primes)
  for(i=0; i < num_points; i++){
    
    prime = check_prime(i);
    
    if(prime==1)
      num_primes++;
    
  }
  
  t2 = omp_get_wtime ();
  
  printf("number of primes=%d found in %d seconds  between 0 and %d\n",num_primes,t2-t1,num_points);
  
  
  return(0);
}


int check_prime(int num){
  
  int i=2;
  
  while(i<=num/2){
    if(num%i==0)
      return 0;
    else
      i++;
  }
  
  return 1;
}





    
