#include<stdio.h>
#include<omp.h>


int main(int argc, char *argv[]){
   int nthreads = 2;
   int tid,ntids; 

   omp_set_num_threads(nthreads);   

#pragma omp parallel  private (tid)    
   {

   tid = omp_get_thread_num(); 
   ntids = omp_get_num_threads(); 

   printf("Hello world from thread %d of %d !\n",tid,ntids); 

   }



return(0); 
}
