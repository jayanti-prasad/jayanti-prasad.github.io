#include<stdio.h>
#include<mpi.h>
#include<math.h>

/*  
 -   This program computes the value of pi by integrating 
     1/(1+x^2) over the limit [0-1]

-    You can use either the Trapazoidal rule or the Mid Point rule for 
     integration by uncommneting the respective line.

-    This is a demonstration program so ignore accuracy if you do not get the 
     expected result debug ! the program.   

                      -- Jayanti Prasad 
*/


double func(double x);
double TrapzoidRule(int, double, double);
double MidpointRule(int, double, double);

int main(int argc, char ** argv){
  int mynode,totalnodes;
  const double global_a=0.0;
  const double global_b=1.0;
  double local_a,local_b,local_sum,answer;
  int level=20;
  double t1,t2; 
  
  MPI_Init(&argc,&argv);

  MPI_Comm_size(MPI_COMM_WORLD,&totalnodes);
  MPI_Comm_rank(MPI_COMM_WORLD,&mynode); 
  
  local_a=global_a+mynode*(global_b-global_a)/totalnodes;
  local_b=global_a+(mynode+1)*(global_b-global_a)/totalnodes;
  
  //local_sum=TrapzoidRule(level,local_a,local_b);
  local_sum=MidpointRule(level,local_a,local_b);
  
  MPI_Reduce(&local_sum,&answer,1,MPI_DOUBLE,
	     MPI_SUM,0,MPI_COMM_WORLD);
  
  if(mynode==0){
    printf("The answer is:%2.14f\n",answer);
  }
  
  MPI_Finalize();
  
  return(0); 
  
}// end of main 

double func(double x){
   double y;
   y=4.0/(1.0+x*x); 
   
   return(y);
}// end of func 

double TrapzoidRule(int level, double a, double b){
  int i,j,nsteps;
  double h, sum;
  j= (int) pow(2.0,level);
  nsteps= j-1;
  
   h=(b-a)/j;
   sum=0.0;
  
   for(i=1; i<=nsteps;i++)
     sum+=func(a+i*h);
   sum*=2;
   
   sum+=func(a)+func(b);
   sum*=0.5*h;
   return (sum);
}

double MidpointRule(int level, double a, double b){
  int i,j,nsteps;
  double h, sum; 
  j = (int) pow(2.0,level);
  nsteps= j-1;
  
  h=(b-a)/j;
  sum=0.0;
  for(i=0; i <= nsteps;i++)
    sum+=func(a+(i+0.5)*h);
  sum*=h;
  return sum;
}




	








		
